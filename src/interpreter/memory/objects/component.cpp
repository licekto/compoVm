#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CComponent::CComponent() {
			}

			CComponent::CComponent(ptr(CComponent) instance) {
				for (ptr(CGeneralPort) port : instance->m_ports) {
					this->m_ports.push_back(new_ptr(CGeneralPort)(port));
				}
				for (ptr(CGeneralService) service : instance->m_services) {
					this->m_services.push_back(new_ptr(CGeneralService)(service));
				}
			}

			CComponent::~CComponent() {
			}

			void CComponent::addPort(ptr(CGeneralPort) port) {
				m_ports.push_back(port);
			}

			size_t CComponent::getNumberOfPorts() const {
				return m_ports.size();
			}

			ptr(CGeneralPort) CComponent::getPortAt(size_t index) {
				if (index < m_ports.size()) {
					return m_ports.at(index);
				}
				// throw exception
				return nullptr;
			}

			ptr(CGeneralPort) CComponent::getPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(CGeneralPort) port) {
					return port->getName() == name;
				});

				if (it == m_ports.end()) {
                                        throw exceptions::runtime::CPortNotFoundException(name);
				}
				return *it;
			}

			std::shared_ptr<CGeneralService> CComponent::getServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](ptr(CGeneralService) service) {
					return service->getName() == name;
				});

				if (it == m_services.end()) {
					//throw exception
				}
				return *it;
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

                        std::stringstream CComponent::dump() const {
                            std::stringstream dump;
                            
                            dump << "ahoj";
                            
                            return dump;
                        }

		}
	}
}