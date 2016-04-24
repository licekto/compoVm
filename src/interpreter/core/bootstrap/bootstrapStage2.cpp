#include "interpreter/core/bootstrap/bootstrapStage2.h"
#include "interpreter/core/interpreter.h"

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
					component->addPort(m_bootstrapStage1->m_memory->newComponentPort(component, port).lock());
				}
			}

			void CBootstrapStage2::addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					component->addService(m_bootstrapStage1->m_memory->newComponentService(component, descriptor->getServiceAt(i)).lock());
				}
			}

			ptr(mem_component) CBootstrapStage2::bootstrapRootComponent(ptr(mem_component) owner) {
				ptr(ast_descriptor) descriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Component");

				ptr(mem_component) component = m_bootstrapStage1->m_memory->newComponent().lock();

				ptr(ast_port) port = descriptor->getPortByName("default");
				ptr(mem_port) generalPort = m_bootstrapStage1->m_memory->newComponentPort(nullptr, port).lock();
				component->addPort(generalPort);

				addPorts(component, descriptor);
				addServices(component, descriptor);

				component->getPortByName("default")->getPort()->getPortByName("owner")->connectPort(component->getPortByName("default"));
				component->getPortByName("default")->getPort()->getPortByName("owner")->setOwner(component);

				if (owner.use_count()) {
					component->getPortByName("owner")->connectPort(owner->getPortByName("default"));
				}
				component->setParent(nullptr);

				component->removeServiceByName("getPortNamed");
				{
					auto callback = [](const ptr(mem_component)& context) -> ptr(mem_port) {
						std::string name = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
						context->getPortByName("args")->disconnectPortAt(0);

						if (context->getPortByName(name)->isPrimitive()) {
							return context->getPortByName(name);
						} else {
							return context->getPortByName(name)->getPort()->getPortByName("default");
						}
					};
					component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "getPortNamed", callback).lock());
				}

				component->removeServiceByName("getIdentityHash");
				{
					auto callback = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
						return m_bootstrapStage1->bootstrapIntValue(context->getHash())->getDefaultPort();
					};
					component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "getIdentityHash", callback).lock());
				}

				return component;
			}

			ptr(mem_component) CBootstrapStage2::buildPortFromDescription(ptr(mem_component) description, ptr(mem_component) owner) {
				bool isCollection = false;

				if (description->getPortByName("isCollectionPort")->getConnectedPortsNumber()) {
					isCollection = cast(mem_bool)(description->getPortByName("isCollectionPort")->getConnectedPortAt(0)->getOwner())->getValue();
				}

				ptr(mem_component) port;
				if (isCollection) {
					port = m_bootstrapStage1->bootstrapCollectionPortComponent(owner);
				} else {
					port = m_bootstrapStage1->bootstrapPortComponent(owner);
				}

				std::string name = cast(mem_string)(description->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue();

				port->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue(name)->getDefaultPort());
				port->getPortByName("interfaceDescription")->connectPort(
				    cloneInterface(description->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner(), owner)
				    ->getPortByName("default"));
				port->getPortByName("isCollection")->connectPort(m_bootstrapStage1->bootstrapBoolValue(isCollection)->getDefaultPort());

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
					}
				} else if (type == PORT_TYPE_INJECTED) {
					throw exceptions::semantic::CUnsupportedFeatureException("Injection port");
				} else if (type == PORT_TYPE_NAMED) {
					std::string componentName = cast(mem_string)(interface->getPortByName("componentName")->getConnectedPortAt(0)->getOwner())->getValue();
					newInterface->getPortByName("componentName")->connectPort(m_bootstrapStage1->bootstrapStringValue(componentName)->getDefaultPort());
				} else if (type == PORT_TYPE_UNIVERSAL) {
					if (portOwner.use_count()) {
						portOwner->connectAllServicesTo(newInterface->getPortByName("services"));
					}
				} else {
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

			ptr(mem_component) CBootstrapStage2::bootstrapPrologue(const std::string& coreDescriptorName) {
				ptr(mem_component) component = m_bootstrapStage1->m_memory->newComponent().lock();
				ptr(ast_descriptor) coreDescriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor(coreDescriptorName);

				ptr(mem_component) parentComponent = bootstrapRootComponent(nullptr);
				component->setParent(parentComponent);
				parentComponent->setChild(component);

				addPorts(component, coreDescriptor);
				addServices(component, coreDescriptor);

				return component;
			}

			void CBootstrapStage2::bootstrapEpilogue(ptr(mem_component) component) {
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
			}

			ptr(mem_component) CBootstrapStage2::bootstrapSystemComponent() {
				ptr(mem_component) newComponent = bootstrapPrologue("System");

				newComponent->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue("System")->getDefaultPort());

				newComponent->removeServiceByName("println");
				newComponent->removeServiceByName("readString");
				newComponent->removeServiceByName("readInt");
				newComponent->removeServiceByName("getRand");

				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
                                        std::string str = m_bootstrapStage1->m_interpreter.lock()
                                                ->getStringRepresentation(cast(mem_value)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner()));
					STANDARD_OUT << str << std::endl;
					return nullptr;
				};
				newComponent->addService(m_bootstrapStage1->m_memory->newPrimitiveService(newComponent, "println", callback).lock());

				callback = [this](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					std::string val;
					STANDARD_IN >> val;
					return getStringComponent(val);
				};
				newComponent->addService(m_bootstrapStage1->m_memory->newPrimitiveService(newComponent, "readString", callback).lock());

				callback = [this](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					i64 val;
					STANDARD_IN >> val;
					return getIntComponent(val);
				};
				newComponent->addService(m_bootstrapStage1->m_memory->newPrimitiveService(newComponent, "readInt", callback).lock());

				callback = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					i64 seed = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					srand(seed);
					return getIntComponent(rand());
				};
				newComponent->addService(m_bootstrapStage1->m_memory->newPrimitiveService(newComponent, "getRand", callback).lock());

				bootstrapEpilogue(newComponent);
				return newComponent;
			}

			ptr(mem_component) CBootstrapStage2::bootstrapServiceDescriptorComponent() {
				ptr(mem_component) component = bootstrapDescriptorComponent(m_bootstrapStage1->m_coreModules->getCoreDescriptor("Service"));

				component->getPortByName("name")->disconnectAll();
				component->getPortByName("parentName")->disconnectAll();

				component->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue("Service")->getDefaultPort());
				component->getPortByName("parentName")->connectPort(m_bootstrapStage1->bootstrapStringValue("Component")->getDefaultPort());

				component->removeServiceByName("new");
				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback = [this, component](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					return m_bootstrapStage1->m_memory->newEmptyServiceComponent().lock()->getPortByName("default");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "new", callback).lock());

				return component;
			}

			ptr(mem_component) CBootstrapStage2::bootstrapPortDescriptionComponent() {
				ptr(mem_component) component = bootstrapDescriptorComponent(m_bootstrapStage1->m_coreModules->getCoreDescriptor("PortDescription"));

				component->getPortByName("name")->disconnectAll();
				component->getPortByName("parentName")->disconnectAll();

				component->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue("PortDescription")->getDefaultPort());
				component->getPortByName("parentName")->connectPort(m_bootstrapStage1->bootstrapStringValue("Component")->getDefaultPort());

				component->removeServiceByName("new");
				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback = [this, component](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					return m_bootstrapStage1->m_memory->newPortDescriptionComponent().lock()->getPortByName("default");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "new", callback).lock());

				return component;
			}

			ptr(mem_component) CBootstrapStage2::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
				ptr(mem_component) component = bootstrapPrologue("Descriptor");

				component->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue(descriptor->getNameSymbol()->getStringValue())->getDefaultPort());
				if (descriptor->getExtendsSymbol().use_count()) {
					component->getPortByName("parentName")->connectPort(m_bootstrapStage1->bootstrapStringValue(descriptor->getExtendsSymbol()->getStringValue())->getDefaultPort());
				} else {
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

				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) newComponent = m_bootstrapStage1->m_memory->newComponent().lock();

					std::string parentName = cast(mem_string)(context->getPortByName("parentName")->getConnectedPortAt(0)->getOwner())->getValue();

					ptr(mem_component) parent;
					if (parentName == "Component") {
						parent = bootstrapRootComponent(nullptr);
					} else {
						parent = m_bootstrapStage1->m_interpreter.lock()->execService(parentName, "new")->getOwner()->getBottomChild();
					}
					newComponent->setParent(parent);
					parent->setChild(newComponent);

					newComponent->getPortByName("descriptorPort")->disconnectAll();
					newComponent->getPortByName("descriptorPort")->connectPort(component->getPortByName("default"));

					for (size_t i = 0; i < context->getPortByName("services")->getConnectedPortsNumber(); ++i) {
						ptr(mem_component) newService = cloneService(context->getPortByName("services")->getConnectedPortAt(i)->getOwner()->getBottomChild(), newComponent);
						std::string serviceName =
						    cast(mem_string)(newService->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner()
						                     ->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();

						ptr(mem_service) specialized;
						if (newComponent->containsService(serviceName)) {
							specialized = newComponent->getServiceByName(serviceName);
						}
						newComponent->addService(m_bootstrapStage1->m_memory->newComponentService(newService, specialized).lock());
					}

					for (size_t i = 0; i < context->getPortByName("ports")->getConnectedPortsNumber(); ++i) {
						ptr(mem_component) portDescriptionComponent = context->getPortByName("ports")->getConnectedPortAt(i)->getOwner();
						std::string visibility = cast(mem_string)(portDescriptionComponent->getPortByName("visibility")->getConnectedPortAt(0)->getOwner())->getValue();
						type_visibility v = visibility == VISIBILITY_EXTERNAL ? type_visibility::EXTERNAL : type_visibility::INTERNAL;
						std::string role = cast(mem_string)(portDescriptionComponent->getPortByName("role")->getConnectedPortAt(0)->getOwner())->getValue();
						type_role r = role == ROLE_REQUIREMENT ? type_role::REQUIRES : type_role::PROVIDES;

						ptr(mem_port) newPort = m_bootstrapStage1->m_memory->newComponentPort(buildPortFromDescription(portDescriptionComponent, newComponent), v, r).lock();
						newComponent->addPort(newPort);
					}

					for (int i = context->getPortByName("architectureDefinition")->getConnectedPortsNumber() - 1; i >= 0; --i) {
						ptr(mem_component) connection = context->getPortByName("architectureDefinition")->getConnectedPortAt(i)->getOwner()->getBottomChild();

						auto func = [this, &connection, &newComponent](const std::string& type, const std::string& portName, const std::string& dstSrc) -> ptr(mem_port) {
							ptr(mem_port) port;
							if (type == CONNECTION_NAMED) {
								std::string componentName = cast(mem_string)(connection->getPortByName(dstSrc + "Component")->getConnectedPortAt(0)->getOwner())->getValue();
								if (componentName == "self") {
									port = newComponent->getPortByName(portName);
								} else {
									port = newComponent->getPortByName(componentName)->getConnectedPortAt(0)->getOwner()->getBottomChild()->getPortByName(portName);
								}
							} else if (type == CONNECTION_COLLECTION) {
								std::string componentName = cast(mem_string)(connection->getPortByName(dstSrc + "Component")->getConnectedPortAt(0)->getOwner())->getValue();
								if (componentName == "self") {
									throw exceptions::runtime::CSelfPortNotCollectionException();
								}
								u64 index = cast(mem_int)(connection->getPortByName(dstSrc + "ComponentIndex")->getConnectedPortAt(0)->getOwner())->getValue();
								port = newComponent->getPortByName(componentName)->getConnectedPortAt(index)->getOwner()->getBottomChild()->getPortByName(portName);
							} else if (type == CONNECTION_INVOCATION) {
								ptr(mem_component) inv = connection->getPortByName(dstSrc + "ComponentInvocation")->getConnectedPortAt(0)->getOwner()->getBottomChild();
								std::string receiverName = cast(mem_string)(inv->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue();
								std::string selectorName = cast(mem_string)(inv->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();

								if (inv->getPortByName("params")->getConnectedPortsNumber()) {
									throw exceptions::runtime::CWrongServiceTypeInArchitectureException();
								} else if (selectorName != "new") {
									throw exceptions::runtime::CWrongServiceTypeInArchitectureException();
								}
								port = m_bootstrapStage1->m_interpreter.lock()->execService(receiverName, selectorName);
							} else if (type == CONNECTION_DEREFERENCE) {
								throw exceptions::semantic::CUnsupportedFeatureException("dereference");
							} else {
								throw exceptions::runtime::CWrongBindTypeException(type);
							}
							return port;
						};
						std::string sourceType = cast(mem_string)(connection->getPortByName("sourceType")->getConnectedPortAt(0)->getOwner())->getValue();
						std::string sourcePortName = cast(mem_string)(connection->getPortByName("sourcePort")->getConnectedPortAt(0)->getOwner())->getValue();
						std::string destinationType = cast(mem_string)(connection->getPortByName("destinationType")->getConnectedPortAt(0)->getOwner())->getValue();
						std::string destinationPortName = cast(mem_string)(connection->getPortByName("destinationPort")->getConnectedPortAt(0)->getOwner())->getValue();

						ptr(mem_port) srcPort = func(sourceType, sourcePortName, "source");
						ptr(mem_port) dstPort = func(destinationType, destinationPortName, "destination");

						checkPortSemantics(srcPort, newComponent);
						checkPortSemantics(dstPort, newComponent);

						std::string bindType = cast(mem_string)(connection->getPortByName("bindType")->getConnectedPortAt(0)->getOwner())->getValue();
						if (bindType == BIND_CONNECTION) {
							srcPort->connectPort(dstPort);
						} else if (bindType == BIND_DISCONNECTION) {
							srcPort->disconnectPortByName(dstPort->getName());
						} else if (bindType == BIND_DELEGATION) {
							srcPort->delegateTo(dstPort);
						} else {
							throw exceptions::runtime::CWrongBindTypeException(bindType);
						}
					}
					return newComponent->getPortByName("default");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "new", callback).lock());

				component->removeServiceByName("getDescribedPortAt");
				callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					i64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectAll();
					return context->getPortByName("ports")->getConnectedPortAt(index);
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "getDescribedPortAt", callback).lock());

				component->removeServiceByName("getDescribedConnAt");
				callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					i64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectAll();
					return context->getPortByName("architectureDefinition")->getConnectedPortAt(index);
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "getDescribedConnAt", callback).lock());

				component->removeServiceByName("newNamed");
				callback = [this, component](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					throw exceptions::semantic::CUnsupportedFeatureException("newNamed() function of Descriptor");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "newNamed", callback).lock());

				component->removeServiceByName("removeConnDescription");
				callback = [this, component](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					throw exceptions::semantic::CUnsupportedFeatureException("removeConnDescription() function of Descriptor");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "removeConnDescription", callback).lock());

				component->removeServiceByName("addConnDescription");
				callback = [this, component](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					throw exceptions::semantic::CUnsupportedFeatureException("addConnDescription() function of Descriptor");
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "addConnDescription", callback).lock());

				component->removeServiceByName("getService");
				callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string searchedName = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					//i64 arity = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(1)->getOwner())->getValue();
					context->getPortByName("args")->disconnectAll();
					for (size_t i = 0; i < context->getPortByName("services")->getConnectedPortsNumber(); ++i) {
						std::string name = cast(mem_string)(context->getPortByName("services")
						                                    ->getConnectedPortAt(i)->getOwner()->getPortByName("serviceSign")
						                                    ->getConnectedPortAt(0)->getOwner()->getPortByName("selector")
						                                    ->getConnectedPortAt(0)->getOwner())->getValue();
						if (name == searchedName) {
							return context->getPortByName("services")->getConnectedPortAt(i);
						}
					}
					throw exceptions::runtime::CServiceNotFoundException(searchedName);
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "getService", callback).lock());

				component->removeServiceByName("removeService");
				callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string searchedName = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					//i64 arity = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(1)->getOwner())->getValue();
					context->getPortByName("args")->disconnectAll();
					for (size_t i = 0; i < context->getPortByName("services")->getConnectedPortsNumber(); ++i) {
						std::string name = cast(mem_string)(context->getPortByName("services")
						                                    ->getConnectedPortAt(i)->getOwner()->getPortByName("serviceSign")
						                                    ->getConnectedPortAt(0)->getOwner()->getPortByName("selector")
						                                    ->getConnectedPortAt(0)->getOwner())->getValue();
						if (name == searchedName) {
							context->getPortByName("services")->disconnectPortAt(i);
							break;
						}
					}
					return nullptr;
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "removeService", callback).lock());

				component->removeServiceByName("removePortDescription");
				callback = [this, component](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string searchedName = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					//i64 arity = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(1)->getOwner())->getValue();
					context->getPortByName("args")->disconnectAll();
					for (size_t i = 0; i < context->getPortByName("ports")->getConnectedPortsNumber(); ++i) {
						std::string name = cast(mem_string)(context->getPortByName("ports")
						                                    ->getConnectedPortAt(i)->getOwner()->getPortByName("name")
						                                    ->getConnectedPortAt(0)->getOwner())->getValue();
						if (name == searchedName) {
							context->getPortByName("ports")->disconnectPortAt(i);
							break;
						}
					}
					return nullptr;
				};
				component->addService(m_bootstrapStage1->m_memory->newPrimitiveService(component, "removePortDescription", callback).lock());

				bootstrapEpilogue(component);

				return component;
			}

			void CBootstrapStage2::checkPortSemantics(ptr(mem_port) port, ptr(mem_component) owner) {
				std::string portName = port->getName();
				if (port->getOwner()->getBottomChild().get() == owner.get()
				        && portName != "default"
				        && port->getVisibility() == type_visibility::EXTERNAL) {
					throw exceptions::semantic::CWrongPortVisibilityException(portName);
				}
				if (port->getOwner()->getBottomChild().get() != owner.get()
				        && port->getVisibility() != type_visibility::EXTERNAL) {
					throw exceptions::semantic::CWrongPortVisibilityException(portName);
				}
			}

		}

	}

}