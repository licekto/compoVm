#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"


namespace interpreter {

	namespace memory {

		namespace objects {

			i64 CComponent::m_pseudoHash = 0;

			CComponent::CComponent() {
				++m_pseudoHash;
			}

			CComponent::~CComponent() {
			}

			void CComponent::addPort(ptr(CGeneralPort) port) {
				m_ports.push_back(port);
			}

			size_t CComponent::getNumberOfPorts() const {
				size_t cnt = m_ports.size();
				ptr(CComponent) tmp = m_parent.lock();
				while (tmp.use_count()) {
					cnt += tmp->m_ports.size();
					tmp = tmp->m_parent.lock();
				}
				tmp = m_child.lock();
				while (tmp.use_count()) {
					cnt += tmp->m_ports.size();
					tmp = tmp->m_child.lock();
				}
				return cnt;
			}

			ptr(CGeneralPort) CComponent::getSelfPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](wptr(CGeneralPort) port) {
					return port.lock()->getName() == name;
				});

				if (it == m_ports.end()) {
					return nullptr;
				}
				//return *it;
				return it.base()->lock();
			}

			ptr(CGeneralPort) CComponent::getPortByName(const std::string& name) {
				ptr(CGeneralPort) port = getSelfPortByName(name);
				if (port.use_count()) {
					return port;
				}

				ptr(CComponent) tmp = m_parent.lock();

				while (tmp.use_count()) {
					port = tmp->getSelfPortByName(name);
					if (port.use_count()) {
						return port;
					}
					tmp = tmp->m_parent.lock();
				}

				tmp = m_child.lock();
				while (tmp.use_count()) {
					port = tmp->getSelfPortByName(name);
					if (port.use_count()) {
						return port;
					}
					tmp = tmp->m_child.lock();
				}
				throw exceptions::runtime::CPortNotFoundException(name);
			}

			size_t CComponent::getNumberOfSelfServices() const {
				return m_services.size();
			}

			size_t CComponent::getNumberOfAllServices() const {
				size_t cnt = m_services.size();
				ptr(CComponent) tmp = m_parent.lock();
				while (tmp.use_count()) {
					cnt += tmp->m_services.size();
					tmp = tmp->m_parent.lock();
				}
				tmp = m_child.lock();
				while (tmp.use_count()) {
					cnt += tmp->m_services.size();
					tmp = tmp->m_child.lock();
				}
				return cnt;
			}

			void CComponent::connectAllSelfServicesTo(ptr(CGeneralPort) port) {
				for (wptr(CGeneralService) service : m_services) {
					if (!service.lock()->isPrimitive()) {
						port->connectPort(service.lock()->getDefaultPort());
					} else {
						port->connectPrimitiveService(service.lock());
					}
				}
			}

			void CComponent::connectAllParentServicesTo(ptr(CGeneralPort) port) {
				ptr(CComponent) tmp = m_parent.lock();

				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_parent.lock();
				}
			}

			void CComponent::connectAllServicesTo(ptr(CGeneralPort) port) {
				connectAllSelfServicesTo(port);
				ptr(CComponent) tmp = m_parent.lock();

				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_parent.lock();
				}

				tmp = m_child.lock();
				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_child.lock();
				}
			}

			ptr(CGeneralService) CComponent::getSelfServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](wptr(CGeneralService) service) {
					return service.lock()->getName() == name;
				});

				if (it == m_services.end()) {
					return nullptr;
				}
				//return *it;
				return it.base()->lock();
			}

			ptr(CGeneralService) CComponent::getServiceByName(const std::string& name) {
				ptr(CGeneralService) service = getSelfServiceByName(name);
				if (service.use_count()) {
					return service;
				}

				ptr(CComponent) tmp = m_parent.lock();

				while (tmp.use_count()) {
					service = tmp->getSelfServiceByName(name);
					if (service.use_count()) {
						return service;
					}
					tmp = tmp->m_parent.lock();
				}

				tmp = m_child.lock();
				while (tmp.use_count()) {
					service = tmp->getSelfServiceByName(name);
					if (service.use_count()) {
						return service;
					}
					tmp = tmp->m_child.lock();
				}
				throw exceptions::runtime::CServiceNotFoundException(name);
			}

			bool CComponent::containsService(const std::string& name) {
				bool ret = true;
				try {
					getServiceByName(name);
				} catch (const exceptions::runtime::CServiceNotFoundException& ex) {
					ret = false;
				}
				return ret;
			}

			void CComponent::addService(ptr(CGeneralService) service) {
				m_services.push_back(service);
			}

			std::shared_ptr<CGeneralPort> CComponent::getPortOfService(const std::string& serviceName) {
				for (wptr(CGeneralPort) port : m_ports) {
					if (port.lock()->isPrimitive()) {
						ptr(primitives::CPrimitivePort) primitivePort = port.lock()->getPrimitivePort();
						for (size_t i = 0; i < primitivePort->getConnectedServicesNumber(); ++i) {
							if (primitivePort->getConnectedServiceAt(i)->getName() == serviceName) {
								return port.lock();
							}
						}
					} else {
						TRACE(ERROR, "Not implemented");
						return nullptr;
					}
				}
				return nullptr;
			}

			void CComponent::removeServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](wptr(CGeneralService) service) {
					return service.lock()->getName() == name;
				});

				if (it != m_services.end()) {
					m_services.erase(it);
				}
			}

			size_t CComponent::getNumberOfInheritedServices() const {
				size_t cnt = 0;
				ptr(CComponent) parent = m_parent.lock();
				while (parent.use_count()) {
					cnt += parent->getNumberOfAllServices();
					parent = parent->getParent();
				}
				return cnt;
			}

			ptr(CComponent) CComponent::getParent() {
				return m_parent.lock();
			}

			ptr(CComponent) CComponent::getTopParent() {
				ptr(CComponent) parent = this->shared_from_this();
				while (parent->m_parent.use_count()) {
					parent = parent->m_parent.lock();
				}
				return parent;
			}

			void CComponent::setParent(ptr(CComponent) parent) {
				m_parent = wptr(CComponent)(parent);
			}

			ptr(CComponent) CComponent::getChild() {
				return m_child.lock();
			}

			ptr(CComponent) CComponent::getBottomChild() {
				ptr(CComponent) child = this->shared_from_this();
				while (child->m_child.use_count()) {
					child = child->m_child.lock();
				}
				return child;
			}

			void CComponent::setChild(ptr(CComponent) child) {
				m_child = wptr(CComponent)(child);
			}

			std::stringstream CComponent::dump() const {
				std::stringstream dump;

				if (m_parent.use_count()) {
					dump << m_parent.lock()->dump().str() << std::endl;
				}

				dump << "ports: " << m_ports.size() << std::endl;
				for (wptr(CGeneralPort) port : m_ports) {
					dump << "\tname: " << port.lock()->getName() << ", connected ports: " << port.lock()->getConnectedPortsNumber() << std::endl;
				}

				dump << "services: " << m_services.size() << std::endl;
				for (wptr(CGeneralService) service : m_services) {
					dump << "\tname: " << service.lock()->getName() << std::endl;
				}

				return dump;
			}

			size_t CComponent::getSelfPortsNumber() {
				return m_ports.size();
			}

			ptr(CGeneralPort) CComponent::getSelfPortAt(size_t index) {
				return m_ports.at(index).lock();
			}

			std::map<std::string, ptr(CGeneralPort)> CComponent::getAllPorts() {
				std::map<std::string, ptr(CGeneralPort)> portsMap;

				ptr(CComponent) tmp = m_parent.lock();

				while (tmp.use_count()) {
					for (size_t i = 0; i < tmp->getSelfPortsNumber(); ++i) {
						portsMap[tmp->getSelfPortAt(i)->getName()] = tmp->getSelfPortAt(i);
					}
					tmp = tmp->m_parent.lock();
				}

				for (size_t i = 0; i < getSelfPortsNumber(); ++i) {
					portsMap[getSelfPortAt(i)->getName()] = getSelfPortAt(i);
				}

				tmp = m_child.lock();
				while (tmp.use_count()) {
					for (size_t i = 0; i < tmp->getSelfPortsNumber(); ++i) {
						portsMap[tmp->getSelfPortAt(i)->getName()] = tmp->getSelfPortAt(i);
					}
					tmp = tmp->m_child.lock();
				}

				return portsMap;
			}

			ptr(CGeneralService) CComponent::lookupService(const std::string& name) {
				return getBottomChild()->getServiceByName(name);
			}

			i64 CComponent::getHash() const {
				return m_pseudoHash;
			}

		}
	}
}