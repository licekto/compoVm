#include "interpreter/core/bootstrap/bootstrapStage2.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			CBootstrapStage2::CBootstrapStage2(ptr(CBootstrapStage1) stage1) : m_bootstrapStage1(stage1) {
			}

			void CBootstrapStage2::addPorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
					ptr(ast_port) port = descriptor->getPortAt(i);
					if (port->getNameSymbol()->getStringValue() == "default") {
						continue;
					}
					component->addPort(new_ptr(mem_port)(m_bootstrapStage1->bootstrapPortComponent(port, component), port->getVisibility(), port->getRole()));
				}
			}

			void CBootstrapStage2::addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					component->addService(new_ptr(mem_service)(m_bootstrapStage1->bootstrapServiceComponent(descriptor->getServiceAt(i), component)));
				}
			}

			ptr(mem_component) CBootstrapStage2::bootstrapRootComponent(ptr(mem_component) owner) {
				ptr(ast_descriptor) descriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Component");

				ptr(mem_component) component = new_ptr(mem_component)();

                                ptr(ast_port) port = descriptor->getPortByName("default");
				ptr(mem_port) generalPort = new_ptr(mem_port)(m_bootstrapStage1->bootstrapPortComponent(port, nullptr), port->getVisibility(), port->getRole());
				component->addPort(generalPort);

				addPorts(component, descriptor);
				addServices(component, descriptor);
                                
                                component->getPortByName("default")->getPort()->getPortByName("owner")->connectPort(component->getPortByName("default"));
                                component->getPortByName("default")->getPort()->getPortByName("owner")->setOwner(component);

                                if (owner.use_count()) {
                                    component->getPortByName("owner")->connectPort(owner->getPortByName("default"));
                                }

				return component;
			}

			ptr(mem_component) CBootstrapStage2::buildPortFromDescription(ptr(mem_component) description, ptr(mem_component) owner) {

				ptr(mem_component) port = m_bootstrapStage1->bootstrapPortComponent(owner);

				std::string name = cast(mem_string)(description->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue();

				port->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue(name)->getDefaultPort());
                                port->getPortByName("interfaceDescription")->connectPort(
                                    cloneInterface(description->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner(), owner)
                                        ->getPortByName("default"));

				return port;
			}

			ptr(mem_component) CBootstrapStage2::cloneInterface(ptr(mem_component) interface, ptr(mem_component) portOwner) {
				ptr(mem_component) newInterface = m_bootstrapStage1->bootstrapInterfaceComponent(portOwner);

                                std::string type = cast(mem_string)(interface->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
                                newInterface->getPortByName("type")->connectPort(m_bootstrapStage1->bootstrapStringValue(type)->getDefaultPort());

				if (type == PORT_TYPE_SIGNATURES) {
                                    for(size_t i = 0; i < interface->getPortByName("signatures")->getConnectedPortsNumber(); ++i) {
                                        ptr(mem_component) sign = cloneSignature(interface->getPortByName("signatures")->getConnectedPortAt(i)->getOwner()->getBottomChild(), newInterface);
                                        newInterface->getPortByName("signatures")->connectPort(sign->getPortByName("default"));
                                        
                                        if (portOwner.use_count()) {
                                            std::string serviceName = cast(mem_string)(sign->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
                                            newInterface->getPortByName("services")->connectPort(portOwner->getServiceByName(serviceName)->getDefaultPort());
                                        }
                                    }
				}
				else if (type == PORT_TYPE_INJECTED) {
					throw exceptions::semantic::CUnsupportedFeatureException("Injection port");
				}
				else if (type == PORT_TYPE_NAMED) {
                                        std::string componentName = cast(mem_string)(interface->getPortByName("componentName")->getConnectedPortAt(0)->getOwner())->getValue();
                                        newInterface->getPortByName("componentName")->connectPort(m_bootstrapStage1->bootstrapStringValue(componentName)->getDefaultPort());
				}
				else if (type == PORT_TYPE_UNIVERSAL) {
                                        if (portOwner.use_count()) {
                                            portOwner->connectAllServicesTo(newInterface->getPortByName("services"));
                                        }
				}
				else {
					throw exceptions::runtime::CUnknownPortTypeException();
				}
                                
				return newInterface;
                        }

                        ptr(mem_component) CBootstrapStage2::cloneSignature(ptr(mem_component) signature, ptr(mem_component) owner) {
                            ptr(mem_component) newSignature = m_bootstrapStage1->bootstrapServiceSignatureComponent(owner);
                            
                            std::string selector = cast(mem_string)(signature->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
                            newSignature->getPortByName("selector")->connectPort(m_bootstrapStage1->bootstrapStringValue(selector)->getDefaultPort());
                            
                            for(size_t i = 0; i < signature->getPortByName("paramNames")->getConnectedPortsNumber(); ++i) {
                                std::string param = cast(mem_string)(signature->getPortByName("paramNames")->getConnectedPortAt(i)->getOwner())->getValue();
                                newSignature->getPortByName("paramNames")->connectPort(m_bootstrapStage1->bootstrapStringValue(param)->getDefaultPort());
                            }
                            return newSignature;
                        }

                        ptr(mem_component) CBootstrapStage2::cloneService(ptr(mem_component) service, ptr(mem_component) owner) {
                                ptr(mem_component) newService = m_bootstrapStage1->bootstrapServiceComponent(owner);
                                
                                ptr(mem_component) sign = cloneSignature(service->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner()->getBottomChild(), newService);
                                newService->getPortByName("serviceSign")->connectPort(sign->getPortByName("default"));
                                
                                std::string code = cast(mem_string)(service->getPortByName("code")->getConnectedPortAt(0)->getOwner())->getValue();
                                newService->getPortByName("code")->connectPort(m_bootstrapStage1->bootstrapStringValue(code)->getDefaultPort());
                                
                                return newService;
                        }

                        ptr(mem_port) CBootstrapStage2::getIntComponent(i64 value) {
                            return m_bootstrapStage1->bootstrapIntValue(value)->getDefaultPort();
                        }

                        ptr(mem_port) CBootstrapStage2::getStringComponent(const std::string& value) {
                            return m_bootstrapStage1->bootstrapStringValue(value)->getDefaultPort();
                        }

                        ptr(mem_port) CBootstrapStage2::getBoolComponent(bool value) {
                            return m_bootstrapStage1->bootstrapBoolValue(value)->getDefaultPort();
                        }

			ptr(mem_component) CBootstrapStage2::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
				ptr(mem_component) parentComponent = bootstrapRootComponent(nullptr);
				ptr(mem_component) component = new_ptr(mem_component)();
				ptr(ast_descriptor) coreDescriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Descriptor");
                                
				component->setParent(parentComponent);
				parentComponent->setChild(component);

				addPorts(component, coreDescriptor);
				addServices(component, coreDescriptor);
                                
				component->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue(descriptor->getNameSymbol()->getStringValue())->getDefaultPort());
                                if (descriptor->getExtendsSymbol().use_count()) {
                                    component->getPortByName("parentName")->connectPort(m_bootstrapStage1->bootstrapStringValue(descriptor->getExtendsSymbol()->getStringValue())->getDefaultPort());
                                }
                                else {
                                    component->getPortByName("parentName")->connectPort(m_bootstrapStage1->bootstrapStringValue("Component")->getDefaultPort());
                                }

				for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
					component->getPortByName("ports")->connectPort(m_bootstrapStage1->bootstrapPortDescriptionComponent(descriptor->getPortAt(i), component)->getPortByName("default"));
				}

				if (descriptor->getArchitecture().use_count()) {
					for (size_t i = 0; i < descriptor->getArchitecture()->getBodySize(); ++i) {
						ptr(ast_bind) bind = descriptor->getArchitecture()->getBodyNodeAt(i);
						component->getPortByName("architectureDefinition")->connectPort(m_bootstrapStage1->bootstrapConnectionDescriptionComponent(bind, component)->getPortByName("default"));
					}
				}

				for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					ptr(ast_service) service = descriptor->getServiceAt(i);
					component->getPortByName("services")->connectPort(m_bootstrapStage1->bootstrapServiceComponent(service, component)->getPortByName("default"));
				}

				component->removeServiceByName("new");

				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback;
				callback = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) newComponent = new_ptr(mem_component)();

					ptr(mem_component) parent = bootstrapRootComponent(nullptr);
					newComponent->setParent(parent);
					parent->setChild(newComponent);

					newComponent->getPortByName("descriptorPort")->connectPort(context->getPortByName("default"));

                                        for (size_t i = 0; i < context->getPortByName("services")->getConnectedPortsNumber(); ++i) {
                                                ptr(mem_component) newService = cloneService(context->getPortByName("services")->getConnectedPortAt(i)->getOwner()->getBottomChild(), newComponent);
                                                newComponent->addService(new_ptr(mem_service)(newService));
                                        }

					for (size_t i = 0; i < context->getPortByName("ports")->getConnectedPortsNumber(); ++i) {
						ptr(mem_component) portDescriptionComponent = context->getPortByName("ports")->getConnectedPortAt(i)->getOwner();
                                                std::string visibility = cast(mem_string)(portDescriptionComponent->getPortByName("visibility")->getConnectedPortAt(0)->getOwner())->getValue();
                                                type_visibility v = visibility == VISIBILITY_EXTERNAL ? type_visibility::EXTERNAL : type_visibility::INTERNAL;
                                                std::string role = cast(mem_string)(portDescriptionComponent->getPortByName("role")->getConnectedPortAt(0)->getOwner())->getValue();
                                                type_role r = role == ROLE_REQUIREMENT ? type_role::REQUIRES : type_role::PROVIDES;
                                                
                                                ptr(mem_port) newPort = new_ptr(mem_port)(buildPortFromDescription(portDescriptionComponent, newComponent), v, r);
                                                newComponent->addPort(newPort);
					}
                                        
                                        for (size_t i = 0; i < context->getPortByName("architectureDefinition")->getConnectedPortsNumber(); ++i) {
                                            ptr(mem_component) connection = context->getPortByName("architectureDefinition")->getConnectedPortAt(0)->getOwner()->getBottomChild();
                                            
                                            auto func = [&connection, &newComponent](const std::string& type, const std::string& portName, const std::string& dstSrc) -> ptr(mem_port) {
                                                ptr(mem_port) port;
                                                if (type == CONNECTION_NAMED) {
                                                    std::string componentName = cast(mem_string)(connection->getPortByName(dstSrc + "Component")->getConnectedPortAt(0)->getOwner())->getValue();
                                                    if (componentName == "self") {
                                                        port = newComponent->getPortByName(portName);
                                                    }
                                                    else {
                                                        port = newComponent->getPortByName(componentName)->getConnectedPortAt(0)->getOwner()->getBottomChild()->getPortByName(portName);
                                                    }
                                                }
                                                else if (type == CONNECTION_COLLECTION) {
                                                    std::string componentName = cast(mem_string)(connection->getPortByName(dstSrc + "Component")->getConnectedPortAt(0)->getOwner())->getValue();
                                                    if (componentName == "self") {
                                                        // throw
                                                        return nullptr;
                                                    }
                                                    u64 index = cast(mem_int)(connection->getPortByName(dstSrc + "ComponentIndex")->getConnectedPortAt(0)->getOwner())->getValue();
                                                    port = newComponent->getPortByName(componentName)->getConnectedPortAt(index)->getOwner()->getBottomChild()->getPortByName(portName);
                                                }
                                                else if (type == CONNECTION_INVOCATION) {
                                                    ptr(mem_component) inv = connection->getPortByName(dstSrc + "ComponentInvocation")->getConnectedPortAt(0)->getOwner()->getBottomChild();
                                                    std::string receiverName = cast(mem_string)(inv->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue();
                                                    std::string selectorName = cast(mem_string)(inv->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
                                                }
                                                else if (type == CONNECTION_DEREFERENCE) {
                                                    // throw
                                                }
                                                else {
                                                    // throw
                                                }
                                                return port;
                                            };
                                            std::string sourceType = cast(mem_string)(connection->getPortByName("sourceType")->getConnectedPortAt(0)->getOwner())->getValue();
                                            std::string sourcePortName = cast(mem_string)(connection->getPortByName("sourcePort")->getConnectedPortAt(0)->getOwner())->getValue();
                                            std::string destinationType = cast(mem_string)(connection->getPortByName("destinationType")->getConnectedPortAt(0)->getOwner())->getValue();
                                            std::string destinationPortName = cast(mem_string)(connection->getPortByName("destinationPort")->getConnectedPortAt(0)->getOwner())->getValue();
                                            
                                            ptr(mem_port) srcPort = func(sourceType, sourcePortName, "source");
                                            ptr(mem_port) dstPort = func(destinationType, destinationPortName, "destination");
                                            
                                            std::string bindType = cast(mem_string)(connection->getPortByName("bindType")->getConnectedPortAt(0)->getOwner())->getValue();
                                            if (bindType == BIND_CONNECTION) {
                                                srcPort->connectPort(dstPort);
                                            }
                                            else if (bindType == BIND_DISCONNECTION) {
                                                srcPort->disconnectPortByName(dstPort->getName());
                                            }
                                            else if (bindType == BIND_DELEGATION) {
                                                srcPort->delegateTo(dstPort);
                                            }
                                            else {
                                                // throw
                                            }
                                        }
                                        
					return newComponent->getPortByName("default");
				};
                                ptr(mem_service) newService = new_ptr(mem_service)(new_ptr(memory::objects::primitives::CPrimitiveService)("new", component, callback));
                                component->addService(newService);

				ptr(mem_port) generalPort = component->getPortByName("default")->getPort()
				              ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
				              ->getPortByName("services");
				component->connectAllServicesTo(generalPort);

				generalPort = component->getPortByName("self")->getPort()
				              ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
				              ->getPortByName("services");
				component->connectAllServicesTo(generalPort);

				generalPort = component->getPortByName("super")->getPort()
				              ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
				              ->getPortByName("services");
				component->connectAllParentServicesTo(generalPort);

				return component;
			}
		}

	}

}