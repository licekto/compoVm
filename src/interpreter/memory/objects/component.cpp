#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"


namespace interpreter {

	namespace memory {

		namespace objects {

			CComponent::CComponent() : m_parent(nullptr), m_child(nullptr) {
			}

			CComponent::CComponent(ptr(CComponent) instance) {
                                m_parent = new_ptr(CComponent)(instance->m_parent);
                            
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
				size_t cnt = m_ports.size();
                                if (m_parent.use_count()) {
                                    cnt += m_parent->getNumberOfPorts();
                                }
                                return cnt;
			}

			ptr(CGeneralPort) CComponent::getPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(CGeneralPort) port) {
					return port->getName() == name;
				});

				if (it == m_ports.end()) {
                                        if (m_parent.use_count()) {
                                            return m_parent->getPortByName(name);
                                        }
                                        if (m_child.use_count()) {
                                            return m_child->getPortByName(name);
                                        }
                                        throw exceptions::runtime::CPortNotFoundException(name);
				}
				return *it;
                        }

                        size_t CComponent::getNumberOfAllServices() const {
                            return getNumberOfSubServices() + getNumberOfInheritedServices();
                        }

                        size_t CComponent::getNumberOfSubServices() const {
                            return m_services.size();
                        }

                        ptr(CGeneralService) CComponent::getServiceAt(size_t index) {
                                ptr(CGeneralService) service;
				try {
					service = m_services.at(index);
				} catch (const std::out_of_range& ex) {
                                        TRACE(ERROR, "Services index out of range exception: " << ex.what());
				}
				return service;
                        }

			ptr(CGeneralService) CComponent::getServiceByName(const std::string& name) {
				auto it = std::find_if(m_services.begin(), m_services.end(), [&name](ptr(CGeneralService) service) {
					return service->getName() == name;
				});

				if (it == m_services.end()) {
                                        if (m_parent.use_count()) {
                                            return m_parent->getServiceByName(name);
                                        }
                                        if (m_child.use_count()) {
                                            return m_child->getServiceByName(name);
                                        }
					throw exceptions::runtime::CServiceNotFoundException(name);
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

                        void CComponent::setParent(ptr(CComponent) parent) {
                                m_parent = parent;
                        }

                        ptr(CComponent) CComponent::getChild() {
                                return m_child;
                        }

                        void CComponent::setChild(ptr(CComponent) child) {
                                m_child = child;
                        }
                        
                        std::stringstream CComponent::dump() const {
                            std::stringstream dump;
                            
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

		}
	}
}