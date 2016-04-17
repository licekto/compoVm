#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"


namespace interpreter {

	namespace memory {

		namespace objects {

			CComponent::CComponent() {
			}

			CComponent::~CComponent() {
			}

			void CComponent::addPort(ptr(CGeneralPort) port) {
				m_ports.push_back(port);
			}

			size_t CComponent::getNumberOfPorts() const {
				size_t cnt = m_ports.size();
				if (m_parent.use_count()) {
					cnt += m_parent->getNumberOfPorts();
				}
				return cnt;
			}

			ptr(CGeneralPort) CComponent::getSelfPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(CGeneralPort) port) {
					return port->getName() == name;
				});

				if (it == m_ports.end()) {
					return nullptr;
				}
				return *it;
			}

			ptr(CGeneralPort) CComponent::getPortByName(const std::string& name) {
				ptr(CGeneralPort) port = getSelfPortByName(name);
				if (port.use_count()) {
					return port;
				}

				ptr(CComponent) tmp = m_parent;

				while (tmp.use_count()) {
					port = tmp->getSelfPortByName(name);
					if (port.use_count()) {
						return port;
					}
					tmp = tmp->m_parent;
				}

				tmp = m_child;
				while (tmp.use_count()) {
					port = tmp->getSelfPortByName(name);
					if (port.use_count()) {
						return port;
					}
					tmp = tmp->m_child;
				}
				throw exceptions::runtime::CPortNotFoundException(name);
			}

			size_t CComponent::getNumberOfSelfServices() const {
				return m_services.size();
			}

			size_t CComponent::getNumberOfAllServices() const {
				return getNumberOfSelfServices() + getNumberOfInheritedServices();
			}

			void CComponent::connectAllSelfServicesTo(ptr(CGeneralPort) port) {
				for (ptr(CGeneralService) service : m_services) {
                                        if (!service->isPrimitive()) {
                                            port->connectPort(service->getDefaultPort());
                                        }
                                        else {
                                            port->connectPrimitiveService(service);
                                        }
				}
			}

			void CComponent::connectAllParentServicesTo(ptr(CGeneralPort) port) {
				ptr(CComponent) tmp = m_parent;

				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_parent;
				}
			}

			void CComponent::connectAllServicesTo(ptr(CGeneralPort) port) {
				connectAllSelfServicesTo(port);
				ptr(CComponent) tmp = m_parent;

				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_parent;
				}

				tmp = m_child;
				while (tmp.use_count()) {
					tmp->connectAllSelfServicesTo(port);
					tmp = tmp->m_child;
				}
			}

			ptr(CGeneralService) CComponent::getSelfServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](ptr(CGeneralService) service) {
					return service->getName() == name;
				});

				if (it == m_services.end()) {
					return nullptr;
				}
				return *it;
			}

			ptr(CGeneralService) CComponent::getServiceByName(const std::string& name) {
				ptr(CGeneralService) service = getSelfServiceByName(name);
				if (service.use_count()) {
					return service;
				}

				ptr(CComponent) tmp = m_parent;

				while (tmp.use_count()) {
					service = tmp->getSelfServiceByName(name);
					if (service.use_count()) {
						return service;
					}
					tmp = tmp->m_parent;
				}

				tmp = m_child;
				while (tmp.use_count()) {
					service = tmp->getSelfServiceByName(name);
					if (service.use_count()) {
						return service;
					}
					tmp = tmp->m_child;
				}
				throw exceptions::runtime::CServiceNotFoundException(name);
			}

			void CComponent::addService(std::shared_ptr<CGeneralService> service) {
				m_services.push_back(service);
			}

			std::shared_ptr<CGeneralPort> CComponent::getPortOfService(const std::string& serviceName) {
				for (ptr(CGeneralPort) port : m_ports) {
					if (port->isPrimitive()) {
						ptr(primitives::CPrimitivePort) primitivePort = port->getPrimitivePort();
						for (size_t i = 0; i < primitivePort->getConnectedServicesNumber(); ++i) {
							if (primitivePort->getConnectedServiceAt(i)->getName() == serviceName) {
								return port;
							}
						}
					} else {
						//ptr(CGeneralPort) generalPort = port->getPort()->getPortByName("connectedPorts");
						TRACE(ERROR, "Not implemented yet");
						return nullptr;
					}
				}
				return nullptr;
			}

			void CComponent::removeServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](ptr(CGeneralService) service) {
					return service->getName() == name;
				});

				if (it != m_services.end()) {
					m_services.erase(it);
				}
			}

			size_t CComponent::getNumberOfInheritedServices() const {
				size_t cnt = 0;
				ptr(CComponent) parent = m_parent;
				while (parent.use_count()) {
					cnt += parent->getNumberOfAllServices();
					parent = parent->getParent();
				}
				return cnt;
			}

			ptr(CComponent) CComponent::getParent() {
				return m_parent;
			}

			ptr(CComponent) CComponent::getTopParent() {
				ptr(CComponent) parent = this->shared_from_this();
				while (parent->m_parent.use_count()) {
					parent = parent->m_parent;
				}
				return parent;
			}

			void CComponent::setParent(ptr(CComponent) parent) {
				m_parent = parent;
			}

			ptr(CComponent) CComponent::getChild() {
				return m_child;
			}

			ptr(CComponent) CComponent::getBottomChild() {
				ptr(CComponent) child = this->shared_from_this();
				while (child->m_child.use_count()) {
					child = child->m_child;
				}
				return child;
			}

			void CComponent::setChild(ptr(CComponent) child) {
				m_child = child;
			}

			std::stringstream CComponent::dump() const {
				std::stringstream dump;

                                if (m_parent) {
                                    dump << m_parent->dump().str() << std::endl;
                                }
                                
				dump << "ports: " << m_ports.size() << std::endl;
				for (ptr(CGeneralPort) port : m_ports) {
					dump << "\tname: " << port->getName() << ", connected ports: " << port->getConnectedPortsNumber() << std::endl;
				}

				dump << "services: " << m_services.size() << std::endl;
				for (ptr(CGeneralService) service : m_services) {
					dump << "\tname: " << service->getName() << std::endl;
				}

				return dump;
                        }

                        size_t CComponent::getSelfPortsNumber() {
                            return m_ports.size();
                        }

                        ptr(CGeneralPort) CComponent::getSelfPortAt(size_t index) {
                            return m_ports.at(index);
                        }

                        std::map<std::string, ptr(CGeneralPort)> CComponent::getAllPorts() {
                                std::map<std::string, ptr(CGeneralPort)> portsMap;

				ptr(CComponent) tmp = m_parent;

				while (tmp.use_count()) {
                                        for (size_t i = 0; i < tmp->getSelfPortsNumber(); ++i) {
                                            portsMap[tmp->getSelfPortAt(i)->getName()] = tmp->getSelfPortAt(i);
                                        }
					tmp = tmp->m_parent;
				}

				tmp = m_child;
				while (tmp.use_count()) {
					for (size_t i = 0; i < tmp->getSelfPortsNumber(); ++i) {
                                            portsMap[tmp->getSelfPortAt(i)->getName()] = tmp->getSelfPortAt(i);
                                        }
					tmp = tmp->m_child;
				}
				
                                return portsMap;
                        }

		}
	}
}