#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "interpreter/memory/objects/values/boolComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CGeneralPort::CGeneralPort(ptr(CComponent) port, types::visibilityType v, types::roleType t)
				: m_port(port), m_visibility(v), m_role(t), m_primitive(false) {

			}

			CGeneralPort::CGeneralPort(ptr(primitives::CPrimitivePort) port, types::visibilityType v, types::roleType t)
				: m_primitivePort(port), m_visibility(v), m_role(t), m_primitive(true) {

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
				return m_port.lock();
			}

			ptr(primitives::CPrimitivePort) CGeneralPort::getPrimitivePort() {
				return m_primitivePort.lock();
			}

			std::string CGeneralPort::getName() const {
				if (m_primitive) {
					return m_primitivePort.lock()->getName();
				} else {
					return cast(memory::objects::values::CStringComponent)
					       (m_port.lock()->getPortByName("name")->getPrimitivePort()->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

			std::shared_ptr<CComponent> CGeneralPort::getOwner() {
				if (m_primitive) {
					return m_primitivePort.lock()->getOwner();
				} else {
					ptr(CGeneralPort) port = m_port.lock()->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0);
					if (port.get() == this) {
						return m_port.lock()->getPortByName("owner")->getPrimitivePort()->getOwner();
					}
					return port->getOwner();
				}
			}

			void CGeneralPort::setOwner(ptr(CComponent) owner) {
				if (m_primitive) {
					m_primitivePort.lock()->setOwner(owner);
				} else {
					return m_port.lock()->getPortByName("owner")->getPrimitivePort()->getConnectedPortAt(0)->setOwner(owner);
				}
			}

			size_t CGeneralPort::getConnectedPortsNumber() const {
				if (m_primitive) {
					return m_primitivePort.lock()->getConnectedPortsNumber();
				} else {
					return m_port.lock()->getPortByName("connectedPorts")->getConnectedPortsNumber();
				}
			}

			std::shared_ptr<objects::CGeneralPort> CGeneralPort::getConnectedPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort.lock()->getConnectedPortAt(index);
				} else {
					return m_port.lock()->getPortByName("connectedPorts")->getConnectedPortAt(index);
				}
			}

			void CGeneralPort::connectPort(std::shared_ptr<objects::CGeneralPort> port) {
				if (m_primitive) {
					if (!isCollection()) {
						//m_primitivePort.lock()->disconnectPortAt(0);
					}
					return m_primitivePort.lock()->connectPort(port);
				} else {
					if (!isCollection()) {
						//m_port.lock()->getPortByName("connectedPorts")->disconnectPortAt(0);
					}
					return m_port.lock()->getPortByName("connectedPorts")->connectPort(port);
				}
			}

			void CGeneralPort::disconnectPortAt(size_t index) {
				if (m_primitive) {
					return m_primitivePort.lock()->disconnectPortAt(index);
				} else {
					return m_port.lock()->getPortByName("connectedPorts")->disconnectPortAt(index);
				}
			}

			void CGeneralPort::disconnectAll() {
				if (m_primitive) {
					return m_primitivePort.lock()->disconnectAll();
				} else {
					return m_port.lock()->getPortByName("connectedPorts")->disconnectAll();
				}
			}

			void CGeneralPort::disconnectPortByName(const std::string& name) {
				if (m_primitive) {
					for (size_t i = 0; i < m_primitivePort.lock()->getConnectedPortsNumber(); ++i) {
						if (m_primitivePort.lock()->getConnectedPortAt(i)->getName() == name) {
							m_primitivePort.lock()->getConnectedPortAt(i)->disconnectPortAt(0);
							break;
						}
					}
				} else {
					m_port.lock()->getPortByName("connectedPorts")->disconnectPortByName(name);
				}
			}

			void CGeneralPort::connectPrimitiveService(ptr(CGeneralService) service) {
				m_connectedPrimitiveServices.push_back(service);
			}

			size_t CGeneralPort::getConnectedPrimitiveServicesNumber() const {
				return m_connectedPrimitiveServices.size();
			}

			ptr(CGeneralService) CGeneralPort::getPrimitiveServiceAt(size_t index) {
				return m_connectedPrimitiveServices.at(index).lock();
			}

			ptr(CGeneralPort) CGeneralPort::invokeByName(const std::string& caller, const std::string& receiver, const std::string& selector, u64 index) {
				if (m_primitive) {
					return m_primitivePort.lock()->getConnectedServiceByName(selector)->invoke();
				} else {
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
						ptr(CGeneralService) callee = port->getOwner()->lookupService(selector);
						return callee->invoke();
					} else if (type == PORT_TYPE_UNIVERSAL) {
                                                //TRACE(DEBUG, port->getOwner().get() << ": " << port->getOwner()->getPortByName("args")->getConnectedPortsNumber());
						ptr(CGeneralService) callee = port->getOwner()->lookupService(selector);
						if (receiver == "super" && selector == caller) {
							callee = callee->getSpecialized();
						}
						return callee->invoke();
					} else if (type == PORT_TYPE_NAMED) {
						if (receiver == "super" && selector == caller) {
							// throw
						}
						return port->getPort()->getPortByName("connectedPorts")->getConnectedPortAt(index)->getOwner()->lookupService(selector)->invoke();
					} else if (type == PORT_TYPE_INJECTED) {
						throw exceptions::semantic::CUnsupportedFeatureException("injected port");
					} else {
						throw exceptions::runtime::CUnknownPortTypeException();
					}
				}
			}

			void CGeneralPort::delegateTo(ptr(CGeneralPort) port) {
				if (m_primitive) {
					m_primitivePort.lock()->delegateToPort(port);
				} else {
					m_port.lock()->getPortByName("delegatedPorts")->connectPort(port);
				}
			}

			ptr(CGeneralPort) CGeneralPort::getDelegatedPort() {
				if (m_primitive) {
					return m_primitivePort.lock()->getDelegatedPort();
				} else {
					if (m_port.lock()->getPortByName("delegatedPorts")->getConnectedPortsNumber()) {
						return m_port.lock()->getPortByName("delegatedPorts")->getConnectedPortAt(0);
					}
					return nullptr;
				}
			}

			bool CGeneralPort::isCollection() const {
				if (m_primitive) {
					return m_primitivePort.lock()->isCollection();
				} else {
					return cast(values::CBoolComponent)(m_port.lock()->getPortByName("isCollection")->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

		}
	}
}
