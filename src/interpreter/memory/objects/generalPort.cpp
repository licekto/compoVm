#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CGeneralPort::CGeneralPort(ptr(CComponent) port, types::visibilityType v, types::roleType t)
				: m_port(port), m_primitivePort(nullptr), m_visibility(v), m_role(t), m_primitive(false) {

			}

			CGeneralPort::CGeneralPort(ptr(primitives::CPrimitivePort) port, types::visibilityType v, types::roleType t)
				: m_port(nullptr), m_primitivePort(port), m_visibility(v), m_role(t), m_primitive(true) {

			}

			types::visibilityType CGeneralPort::getVisibility() const {
				return m_visibility;
			}

			types::roleType CGeneralPort::getRole() const {
				return m_role;
			}

			bool CGeneralPort::isPrimitive() const {
				return m_primitive;
			}

			ptr(CComponent) CGeneralPort::getPort() {
				return m_port;
			}

			ptr(primitives::CPrimitivePort) CGeneralPort::getPrimitivePort() {
				return m_primitivePort;
			}

			std::string CGeneralPort::getName() const {
				if (m_primitive) {
					return m_primitivePort->getName();
				} else {
					return cast(memory::objects::values::CStringComponent)
					       (m_port->getPortByName("name")->getPrimitivePort()->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

			std::shared_ptr<CComponent> CGeneralPort::getOwner() {
				if (m_primitive) {
					return m_primitivePort->getOwner();
				} else {
					ptr(CGeneralPort) port = m_port->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0);
                                        if (port.get() == this) {
                                            return m_port->getPortByName("owner")->getPrimitivePort()->getOwner();
                                        }
                                        return port->getOwner();
				}
			}

			void CGeneralPort::setOwner(ptr(CComponent) owner) {
				if (m_primitive) {
					m_primitivePort->setOwner(owner);
				} else {
					return m_port->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0)->setOwner(owner);
				}
			}

			size_t CGeneralPort::getConnectedPortsNumber() const {
				if (m_primitive) {
					return m_primitivePort->getConnectedPortsNumber();
				} else {
					return m_port->getPortByName("connectedPorts")->getConnectedPortsNumber();
				}
			}

			std::shared_ptr<objects::CGeneralPort> CGeneralPort::getConnectedPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort->getConnectedPortAt(index);
				} else {
					return m_port->getPortByName("connectedPorts")->getConnectedPortAt(index);
				}
			}

			void CGeneralPort::connectPort(std::shared_ptr<objects::CGeneralPort> port) {
				if (m_primitive) {
					return m_primitivePort->connectPort(port);
				} else {
					return m_port->getPortByName("connectedPorts")->connectPort(port);
				}
			}

			void CGeneralPort::disconnectPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort->disconnectPortAt(index);
				} else {
					return m_port->getPortByName("connectedPorts")->disconnectPortAt(index);
				}
                        }

                        void CGeneralPort::disconnectPortByName(const std::string& name) {
                            if (m_primitive) {
                                for (size_t i = 0; i < m_primitivePort->getConnectedPortsNumber(); ++i) {
                                    if (m_primitivePort->getConnectedPortAt(i)->getName() == name) {
                                        m_primitivePort->getConnectedPortAt(i)->disconnectPortAt(0);
                                        break;
                                    }
                                }
                            }
                            else {
                                m_port->getPortByName("connectedPorts")->disconnectPortByName(name);
                            }
                        }

                        void CGeneralPort::connectPrimitiveService(ptr(CGeneralService) service) {
                                m_connectedPrimitiveServices.push_back(service);
                        }

                        size_t CGeneralPort::getConnectedPrimitiveServicesNumber() const {
                                return m_connectedPrimitiveServices.size();
                        }

                        ptr(CGeneralService) CGeneralPort::getPrimitiveServiceAt(size_t index) {
                                return m_connectedPrimitiveServices.at(index);
                        }

                        ptr(CGeneralPort) CGeneralPort::invokeByName(const std::string& selector, u64 index) {
                            if (m_primitive) {
                                return m_primitivePort->getConnectedServiceByName(selector)->invoke();
                            }
                            else {
                                ptr(CGeneralPort) port = this->shared_from_this();
                                
                                while (!port->getOwner()->containsService(selector)) {
                                    port = port->getDelegatedPort();
                                    if (!port.use_count()) {
                                        throw exceptions::runtime::CServiceNotFoundException(selector);
                                    }
                                }
                                
                                std::string type = cast(objects::values::CStringComponent)
                                        (port->getPort()->getPortByName("interfaceDescription")->getConnectedPortAt(0)
                                               ->getOwner()->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
                                
                                if (!port->getOwner()->getServiceByName(selector)->isPrimitive()) {
                                    port->getOwner()->getServiceByName(selector)->getService()->getPortByName("args")->delegateTo(getOwner()->getPortByName("args"));
                                }
                                
                                if (type == PORT_TYPE_SIGNATURES) {
                                    bool found = false;
                                    std::string definedSelector = "";
                                    ptr(CComponent) interface = port->getPort()->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner();
                                    for (size_t i = 0; i < interface->getPortByName("signatures")->getConnectedPortsNumber(); ++i) {
                                        ptr(CComponent) signatures = interface->getPortByName("signatures")->getConnectedPortAt(i)->getOwner();
                                        ptr(CComponent) component = signatures->getPortByName("selector")->getConnectedPortAt(0)->getOwner();
                                        definedSelector = cast(objects::values::CStringComponent)(component)->getValue();
                                        if (definedSelector == selector) {
                                            found = true;
                                            break;
                                        }
                                    }
                                    if (!found) {
                                        throw exceptions::runtime::CServiceNotFoundException(selector);
                                    }
                                    return port->getOwner()->getServiceByName(selector)->invoke();
                                }
                                else if (type == PORT_TYPE_UNIVERSAL) {
                                    return port->getOwner()->getServiceByName(selector)->invoke();
                                }
                                else if (type == PORT_TYPE_NAMED) {
                                    return port->getPort()->getPortByName("connectedPorts")->getConnectedPortAt(index)->getOwner()->getServiceByName(selector)->invoke();
                                }
                                else if (type == PORT_TYPE_INJECTED) {
                                    throw exceptions::semantic::CUnsupportedFeatureException("injected port");
                                }
                                else {
                                    throw exceptions::runtime::CUnknownPortTypeException();
                                }
                            }
                        }

                        void CGeneralPort::delegateTo(ptr(CGeneralPort) port) {
                            if (m_primitive) {
                                m_primitivePort->delegateToPort(port);
                            }
                            else {
                                m_port->getPortByName("delegatedPorts")->connectPort(port);
                            }
                        }

                        ptr(CGeneralPort) CGeneralPort::getDelegatedPort() {
                            if (m_primitive) {
                                return m_primitivePort->getDelegatedPort();
                            }
                            else {
                                if (m_port->getPortByName("delegatedPorts")->getConnectedPortsNumber()) {
                                    return m_port->getPortByName("delegatedPorts")->getConnectedPortAt(0);
                                }
                                return nullptr;
                            }
                        }

                        bool CGeneralPort::isCollection() const {
                            return false;
                        }

		}
	}
}
