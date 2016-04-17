#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "interpreter/core/interpreter.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			CBootstrapStage1::CBootstrapStage1(ptr(core::CCoreModules) coreModules, ptr(core::CInterpreter) interpreter)
				: m_coreModules(coreModules),
				  m_interpreter(interpreter) {
				m_coreModules->loadCoreModules();
                        }

                        void CBootstrapStage1::setInterpreter(ptr(core::CInterpreter) interpreter) {
                                m_interpreter = interpreter;
                        }

			void CBootstrapStage1::addPrimitiveServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor,
			        std::map<std::string, ptr(mem_primitiveservice)>& servicesNames) {

				for(size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					ptr(ast_service) astService = descriptor->getServiceAt(i);

					std::string serviceName = astService->getNameSymbol()->getStringValue();

					ptr(mem_primitiveservice) primitiveService =
					    new_ptr(mem_primitiveservice)(serviceName, component);

					for (size_t j = 0; j < astService->getParamsSize(); ++j) {
						primitiveService->setArgumentName(cast(ast::nodes::procedural::CSymbol)(astService->getParamAt(j))->getStringValue());
					}

					servicesNames[serviceName] = primitiveService;
					component->addService(new_ptr(mem_service)(primitiveService));
				}

			}

			void CBootstrapStage1::addPrimitivePorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
					ptr(ast_port) port = descriptor->getPortAt(i);

					types::visibilityType visibility = port->getVisibility();

					types::roleType role = port->getRole();

					std::string name = port->getNameSymbol()->getStringValue();

					ptr(mem_primitiveport) primitivePort = new_ptr(mem_primitiveport)(name, component);

					ptr(mem_port) generalPort = new_ptr(mem_port)(primitivePort, visibility, role);

					component->addPort(generalPort);
				}
			}

			void CBootstrapStage1::addDefaultPort(ptr(mem_value) value) {
				ptr(mem_primitiveport) primitivePort = new_ptr(mem_primitiveport)("default", value);
				ptr(mem_port) generalPort = new_ptr(mem_port)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
				value->addDefaultPort(generalPort);
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPrologueWithComponent(ptr(ast_descriptor) descriptor,
			        std::map<std::string,ptr(mem_primitiveservice)>& servicesNames,
			        ptr(mem_component) owner) {
                            
				ptr(mem_component) parentComponent = bootstrapComponent(owner);

				ptr(mem_component) component = new_ptr(mem_component)();
				addPrimitivePorts(component, descriptor);
				addPrimitiveServices(component, descriptor, servicesNames);

				component->setParent(parentComponent);
				parentComponent->setChild(component);

				return component;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPrologue(ptr(ast_descriptor) descriptor,
			        std::map<std::string,ptr(mem_primitiveservice)>& servicesNames) {
                            
				ptr(mem_component) component = new_ptr(mem_component)();
				addPrimitivePorts(component, descriptor);
				addPrimitiveServices(component, descriptor, servicesNames);
				return component;
			}

			void CBootstrapStage1::bootstrapEpilogue(ptr(mem_component) component,
			        std::map<std::string,ptr(mem_primitiveservice) >& servicesNames) {
				ptr(mem_primitiveport) defaultPort = component->getPortByName("default")->getPrimitivePort();
				ptr(mem_primitiveport) selfPort = component->getPortByName("self")->getPrimitivePort();

				for(auto const &record : servicesNames) {
					defaultPort->connectService(new_ptr(mem_service)(record.second));
					selfPort->connectService(new_ptr(mem_service)(record.second));
				}
			}

			ptr(mem_int) CBootstrapStage1::bootstrapIntValue(i64 value) {
				ptr(mem_int) component = new_ptr(mem_int)(value);
				addDefaultPort(component);
				return component;
			}

			ptr(mem_string) CBootstrapStage1::bootstrapStringValue(const std::string& value) {
				ptr(mem_string) component = new_ptr(mem_string)(value);
				addDefaultPort(component);
				return component;
			}

			ptr(mem_bool) CBootstrapStage1::bootstrapBoolValue(bool value) {
				ptr(mem_bool) component = new_ptr(mem_bool)(value);
				addDefaultPort(component);
				return component;
			}

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component) >&, const ptr(mem_component)&)>
			CBootstrapStage1::prepareStringSetter(const std::string& portName) {

				return [portName](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);

					ptr(mem_string) param = cast(mem_string)(paramComponent);
					context->getPortByName(portName)->disconnectPortAt(0);
					context->getPortByName(portName)->connectPort(param->getDefaultPort());
					return nullptr;
				};
			}

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component) >&, const ptr(mem_component)&)>
			CBootstrapStage1::prepareStringGetter(const std::string& portName) {
				return [portName](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName(portName)->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
			}

			ptr(mem_component) CBootstrapStage1::bootstrapComponent(ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) component = bootstrapPrologue(m_coreModules->getCoreDescriptor("Component"), servicesNames);

				if (owner.use_count()) {
					ptr(mem_port) port = owner->getPortByName("default");
                                        if (component->getPortByName("owner")->getConnectedPortsNumber()) {
                                            component->getPortByName("owner")->disconnectPortAt(0);
                                        }
					component->getPortByName("owner")->connectPort(port);
				}

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					//return context->getPortByName("")
					return nullptr;
				};
				servicesNames.at("getPorts")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_string) name =
					    cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());

					context->getPortByName("args")->disconnectPortAt(0);

					return context->getPortByName(name->getValue());
				};
				servicesNames.at("getPortNamed")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					if (context->getPortByName("descriptorPort")->getConnectedPortsNumber()) {
						return context->getPortByName("descriptorPort")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames.at("getDescriptor")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					if (context->getPortByName("owner")->getConnectedPortsNumber()) {
						return context->getPortByName("owner")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames.at("getOwner")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					//return new_ptr(memory::objects::CUnsignedIntComponent)(std::hash<mem_component>()(context.get()));
					return 0;
				};
				servicesNames.at("getIdentityHash")->setCallback(callback);

				bootstrapEpilogue(component, servicesNames);
				return component;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				ptr(mem_component) port = bootstrapPortComponent(owner);

				std::string name = astPort->getNameSymbol()->getStringValue();

				port->getPortByName("name")->connectPort(bootstrapStringValue(name)->getDefaultPort());
				port->getPortByName("interfaceDescription")->connectPort(bootstrapInterfaceComponent(astPort, port, owner)->getPortByName("default"));

				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortComponent(ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) port = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Port"), servicesNames, owner);

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;
				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("name")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getName")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getInterface")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {

					ptr(mem_component) calleeComponent = context->getPortByName("owner")->getConnectedPortAt(0)->getOwner();

					ptr(mem_component) argComponent = calleeComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					ptr(mem_string) stringComponent = cast(mem_string)(argComponent);
					std::string serviceName = stringComponent->getValue();

					context->getPortByName("args")->disconnectPortAt(0);

					ptr(mem_primitiveservice) primitiveService = calleeComponent->getServiceByName(serviceName)->getPrimitiveService();

					ptr(mem_port) generalPort = calleeComponent->getPortOfService(primitiveService->getName());

					ptr(mem_string) type = cast(mem_string)(context->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()->getPortByName("type")->getOwner());

					if (type->getValue() == PORT_TYPE_NAMED) {
						ptr(mem_component) connectedComponent = context->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner();
						ptr(mem_service) service = connectedComponent->getServiceByName(serviceName);

						return service->invoke();
					}
					return nullptr;
				};
				servicesNames.at("invoke")->setCallback(callback);

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					bool connected = context->getPortByName("connectedPorts")->getConnectedPortsNumber() > 0;
					return bootstrapBoolValue(connected)->getDefaultPort();
				};
				servicesNames.at("isConnected")->setCallback(callback);

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					bool connected = context->getPortByName("delegatedPorts")->getConnectedPortsNumber() > 0;
					return bootstrapBoolValue(connected)->getDefaultPort();
				};
				servicesNames.at("isDelegated")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->disconnectPortAt(0);
					context->getPortByName("connectedPorts")->connectPort(context->getPortByName("args")->getConnectedPortAt(0));
					context->getPortByName("args")->disconnectPortAt(0);
					return nullptr;
				};
				servicesNames.at("connectTo")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->disconnectPortAt(0);
					return nullptr;
				};
				servicesNames.at("disconnectPort")->setCallback(callback);

				bootstrapEpilogue(port, servicesNames);
				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				ptr(mem_component) port = bootstrapPortComponent(astPort, owner);

				port->removeServiceByName("invoke");
				port->removeServiceByName("disconnectPort");
				port->removeServiceByName("connectTo");

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;
				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					std::string name = cast(mem_string)(arg)->getValue();

					arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
					u64 index = cast(mem_int)(arg)->getValue();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("args")->disconnectPortAt(1);

					cast(mem_string)(context->getPortByName("paramNames")->getConnectedPortAt(index)->getOwner())->setValue(name);
					return nullptr;
				};
				std::vector<std::string> argumentsNames;
				argumentsNames.push_back("name");
				argumentsNames.push_back("index");
				ptr(mem_service) srv = new_ptr(mem_service)(new_ptr(mem_primitiveservice)("invoke", port, callback, argumentsNames));
				port->addService(srv);
				port->getPortByName("default")->getPrimitivePort()->connectService(srv);
				port->getPortByName("self")->getPrimitivePort()->connectService(srv);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 val = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("connectedPorts")->disconnectPortAt(val);
					return nullptr;
				};
				argumentsNames.clear();
				argumentsNames.push_back("index");
				srv = new_ptr(mem_service)(new_ptr(mem_primitiveservice)("disconnectPort", port, callback, argumentsNames));
				port->addService(srv);
				port->getPortByName("default")->getPrimitivePort()->disconnectServiceByName("disconnectPort");
				port->getPortByName("self")->getPrimitivePort()->disconnectServiceByName("disconnectPort");
				port->getPortByName("default")->getPrimitivePort()->connectService(srv);
				port->getPortByName("self")->getPrimitivePort()->connectService(srv);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->connectPort(context->getPortByName("args")->getConnectedPortAt(0));
					context->getPortByName("args")->disconnectPortAt(0);
					return nullptr;
				};
				argumentsNames.clear();
				argumentsNames.push_back("port");
				srv = new_ptr(mem_service)(new_ptr(mem_primitiveservice)("connectTo", port, callback, argumentsNames));
				port->addService(srv);
				port->getPortByName("default")->getPrimitivePort()->disconnectServiceByName("connectTo");
				port->getPortByName("self")->getPrimitivePort()->disconnectServiceByName("connectTo");
				port->getPortByName("default")->getPrimitivePort()->connectService(srv);
				port->getPortByName("self")->getPrimitivePort()->connectService(srv);

				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapServiceComponent(ptr(ast_service) astService, ptr(mem_component) owner) {
				ptr(mem_component) service = bootstrapServiceComponent(owner);

				service->getPortByName("serviceSign")->connectPort(bootstrapServiceSignatureComponent(astService->getSignature(), owner)->getPortByName("default"));
				service->getPortByName("code")->connectPort(cast(mem_string)(bootstrapStringValue(astService->getBodyCode()))->getDefaultPort());
                                
                                if (m_coreModules.use_count()) {
                                    m_coreModules->getParser()->clearAll();
                                    m_coreModules->getParser()->parse(astService->getBodyCode());
                                    astService->setParsedBodyNode(m_coreModules->getParser()->getServiceBody());
                                    m_coreModules->getParser()->clearAll();

                                    for (size_t i = 0; i < astService->getTemporariesSize(); ++i) {
                                        std::string temporary = astService->getTemporaryAt(i)->getStringValue();
                                        service->getPortByName("tempsN")->connectPort(cast(mem_string)(bootstrapStringValue(temporary))->getDefaultPort());
                                    }
                                    
                                    ptr(ast::visitors::CConstantsVisitor) visitor = new_ptr(ast::visitors::CConstantsVisitor)();
                                    astService->accept(visitor);
                                    
                                    for (size_t i = 0; i < visitor->getConstantsSize(); ++i) {
                                        type_node t = visitor->getConstantAt(i)->getNodeType();
                                        ptr(ast_primaryexpression) pex = visitor->getConstantAt(i);
                                        ptr(mem_value) val;
                                        switch(t) {
                                            case type_node::CONSTANT : {
                                                val = bootstrapIntValue(cast(ast_constant)(pex)->getValue());
                                                break;
                                            }
                                            case type_node::STRING_LITERAL : {
                                                val = bootstrapStringValue(cast(ast_string)(pex)->getValue());
                                                break;
                                            }
                                            case type_node::BOOLEAN : {
                                                val = bootstrapBoolValue(cast(ast_boolean)(pex)->getValue());
                                                break;
                                            }
                                            default : {
                                                // throw
                                            }
                                        }
                                        service->getPortByName("tempsV")->connectPort(val->getDefaultPort());
                                    }
                                }
                                
				return service;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapServiceComponent(ptr(mem_component) owner) {
				ptr(mem_component) service = bootstrapComponent(owner);

				addPrimitivePorts(service, m_coreModules->getCoreDescriptor("Service"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> executeCallback =
				[this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					if (contextComponent.use_count()) {
						ptr(mem_string) code = cast(mem_string)(contextComponent->getPortByName("code")->getConnectedPortAt(0)->getOwner());
                                                
                                                ptr(interpreter::core::CContext) context = new_ptr(interpreter::core::CContext)();
                                                
                                                ptr(mem_component) sign = contextComponent->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner();
                                                for (size_t i = 0; i < sign->getPortByName("paramNames")->getConnectedPortsNumber(); ++i) {
                                                    std::string paramName = cast(mem_string)(sign->getPortByName("paramNames")->getConnectedPortAt(i)->getOwner())->getValue();
                                                    ptr(mem_port) port = contextComponent->getPortByName("args")->getConnectedPortAt(i);
                                                    context->setVariable(paramName, port);
                                                }
                                                
						m_interpreter->execServiceCode(code->getValue(), context);
					}
					return nullptr;
				};

				ptr(mem_service) executeService = new_ptr(mem_service)(new_ptr(mem_primitiveservice)("execute", service, executeCallback));

				service->addService(executeService);

				service->getPortByName("default")->getPrimitivePort()->connectService(executeService);
				service->getPortByName("self")->getPrimitivePort()->connectService(executeService);

				return service;
			}
                        
			ptr(mem_component) CBootstrapStage1::bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature, ptr(mem_component) owner) {
				ptr(mem_component) serviceSignature = bootstrapServiceSignatureComponent(owner);

				serviceSignature->getPortByName("selector")->connectPort(cast(mem_string)(bootstrapStringValue(astSignature->getNameSymbol()->getStringValue()))->getDefaultPort());

				ptr(mem_port) paramNames = serviceSignature->getPortByName("paramNames");

				for(size_t i = 0; i < astSignature->getParamsSize(); ++i) {
					std::string param = cast(ast_symbol)(astSignature->getParamAt(i))->getStringValue();
					paramNames->connectPort(bootstrapStringValue(param)->getDefaultPort());
				}
				return serviceSignature;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapServiceSignatureComponent(ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) serviceSignature = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ServiceSignature"), servicesNames, owner);

				servicesNames.at("setSelector")->setCallback(prepareStringSetter("selector"));
				servicesNames.at("getSelector")->setCallback(prepareStringGetter("selector"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback
				= [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 count = context->getPortByName("paramNames")->getConnectedPortsNumber();
					return bootstrapIntValue(count)->getDefaultPort();
				};
				servicesNames.at("getParamsCount")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {

					ptr(mem_port) params = context->getPortByName("paramNames");
					ptr(mem_component) indexComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);

					ptr(mem_int) uintComponent = cast(mem_int)(indexComponent);

					ptr(mem_port) portComp = params->getConnectedPortAt(uintComponent->getValue());

					return portComp->getOwner()->getPortByName("default");
				};
				servicesNames.at("getParamName")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {

					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					u64 index = cast(mem_int)(arg)->getValue();

					arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
					std::string name = cast(mem_string)(arg)->getValue();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("args")->disconnectPortAt(0);

					cast(mem_string)(context->getPortByName("paramNames")->getConnectedPortAt(index)->getOwner())->setValue(name);
					return nullptr;
				};
				servicesNames.at("setParamName")->setCallback(callback);

				bootstrapEpilogue(serviceSignature, servicesNames);
				return serviceSignature;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortDescriptionComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) portDescription = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("PortDescription"), servicesNames, owner);

				portDescription->getPortByName("name")->connectPort(bootstrapStringValue(astPort->getNameSymbol()->getStringValue())->getDefaultPort());
				std::string role = astPort->getRole() == types::roleType::PROVIDES ? ROLE_PROVISION : ROLE_REQUIREMENT;
				portDescription->getPortByName("role")->connectPort(bootstrapStringValue(role)->getDefaultPort());
				std::string visibility = astPort->getVisibility() == types::visibilityType::EXTERNAL ? VISIBILITY_EXTERNAL : VISIBILITY_INTERNAL;
				portDescription->getPortByName("visibility")->connectPort(bootstrapStringValue(visibility)->getDefaultPort());
				if (astPort->getKindOf().use_count()) {
					portDescription->getPortByName("kind")->connectPort(bootstrapStringValue(astPort->getKindOf()->getStringValue())->getDefaultPort());
				}
				portDescription->getPortByName("isCollectionPort")->connectPort(bootstrapBoolValue(astPort->isCollection())->getDefaultPort());

				portDescription->getPortByName("interfaceDefinition")->connectPort(bootstrapInterfaceComponent(astPort, owner, nullptr)->getPortByName("default"));

				servicesNames.at("setName")->setCallback(prepareStringSetter("name"));
				servicesNames.at("getName")->setCallback(prepareStringGetter("name"));

				servicesNames.at("setRole")->setCallback(prepareStringSetter("role"));
				servicesNames.at("getRole")->setCallback(prepareStringGetter("role"));

				servicesNames.at("setKind")->setCallback(prepareStringSetter("kind"));
				servicesNames.at("getKind")->setCallback(prepareStringGetter("kind"));

				servicesNames.at("setVisibility")->setCallback(prepareStringSetter("visibility"));
				servicesNames.at("getVisibility")->setCallback(prepareStringGetter("visibility"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("interfaceDefinition")->disconnectPortAt(0);
					context->getPortByName("interfaceDefinition")->connectPort(paramComponent->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("setInterface")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getInterface")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_bool) paramComponent = cast(mem_bool)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("isCollectionPort")->disconnectPortAt(0);
					context->getPortByName("isCollectionPort")->connectPort(paramComponent->getDefaultPort());
					return nullptr;
				};
				servicesNames.at("setIsCollection")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_bool)(context->getPortByName("isCollectionPort")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames.at("isCollection")->setCallback(callback);

				bootstrapEpilogue(portDescription, servicesNames);
				return portDescription;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapServiceInvocationComponent(ptr(ast_serviceinvocation) astServiceInv, ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) invocation = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ServiceInvocation"), servicesNames, owner);

				invocation->getPortByName("receiver")->connectPort(bootstrapStringValue(astServiceInv->getReceiverName()->getStringValue())->getDefaultPort());
				invocation->getPortByName("selector")->connectPort(bootstrapStringValue(astServiceInv->getSelectorName()->getStringValue())->getDefaultPort());

				if (astServiceInv->getParameters()->getNodeType() == type_node::SERVICE_INVOCATION) {
					invocation->getPortByName("params")->connectPort(bootstrapServiceInvocationComponent
					        (cast(ast_serviceinvocation)(astServiceInv->getParameters()), owner)->getPortByName("default"));
				} else if (astServiceInv->getParameters()->getNodeType() == type_node::SERVICE_SIGNATURE) {
					ptr(ast_servicesignature) sign = cast(ast_servicesignature)(astServiceInv->getParameters());
					for (size_t i = 0; i < sign->getParamsSize(); ++i) {
						switch (sign->getParamAt(i)->getNodeType()) {
						case type_node::STRING_LITERAL : {
							invocation->getPortByName("params")->connectPort(bootstrapStringValue(cast(ast_string)(sign->getParamAt(i))->getValue())->getDefaultPort());
							break;
						}
						case type_node::SYMBOL : {
							invocation->getPortByName("params")->connectPort(bootstrapStringValue(cast(ast_symbol)(sign->getParamAt(i))->getStringValue())->getDefaultPort());
							break;
						}
						case type_node::CONSTANT : {
							invocation->getPortByName("params")->connectPort(bootstrapIntValue(cast(ast_constant)(sign->getParamAt(i))->getValue())->getDefaultPort());
							break;
						}
						case type_node::SERVICE_INVOCATION : {
							invocation->getPortByName("params")->connectPort(bootstrapServiceInvocationComponent(
							            cast(ast_serviceinvocation)(sign->getParamAt(i)), invocation)->getPortByName("default"));
							break;
						}
						default : {
							// throw
							break;
						}
						}
					}
				} else {
					// throw
				}

				servicesNames.at("setReceiver")->setCallback(prepareStringSetter("receiver"));
				servicesNames.at("getReceiver")->setCallback(prepareStringGetter("receiver"));
				servicesNames.at("setSelector")->setCallback(prepareStringSetter("selector"));
				servicesNames.at("getSelector")->setCallback(prepareStringGetter("selector"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return bootstrapIntValue(context->getPortByName("params")->getConnectedPortsNumber())->getDefaultPort();
				};
				servicesNames.at("getParamsCount")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					u64 index = cast(mem_int)(arg)->getValue();
					return context->getPortByName("params")->getConnectedPortAt(index)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getParamAt")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("params")->connectPort(arg->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("addParam")->setCallback(callback);

				bootstrapEpilogue(invocation, servicesNames);
				return invocation;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind, ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) connection = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ConnectionDescription"), servicesNames, owner);

				type_node type = bind->getSourcePortIdentification()->getComponent()->getNodeType();
				switch(type) {
				case type_node::STRING_LITERAL :
				case type_node::SYMBOL : {
					std::string sourceComponentName = cast(ast_symbol)(bind->getSourcePortIdentification()->getComponent())->getStringValue();
					connection->getPortByName("sourceComponent")->connectPort(bootstrapStringValue(sourceComponentName)->getDefaultPort());
					connection->getPortByName("sourceType")->connectPort(bootstrapStringValue(CONNECTION_NAMED)->getDefaultPort());
					break;
				}
				case type_node::SERVICE_INVOCATION : {
					connection->getPortByName("sourceComponentInvocation")->connectPort(
					    bootstrapServiceInvocationComponent(cast(ast_serviceinvocation)(bind->getSourcePortIdentification()->getComponent()), connection)
					    ->getPortByName("default"));
					connection->getPortByName("sourceType")->connectPort(bootstrapStringValue(CONNECTION_INVOCATION)->getDefaultPort());
					break;
				}
				case type_node::COLLECTION_PORT : {
					//ptr(ast_expression) expr = cast(ast_collectionportliteral)(bind->getSourcePortIdentification()->getComponent())->getIndexExpression();
					connection->getPortByName("sourceType")->connectPort(bootstrapStringValue(CONNECTION_COLLECTION)->getDefaultPort());
					break;
				}
				case type_node::DEREFERENCE : {
					connection->getPortByName("sourceType")->connectPort(bootstrapStringValue(CONNECTION_DEREFERENCE)->getDefaultPort());
					break;
				}
				default : {
					throw exceptions::runtime::CUnknownAstNodeTypeException(typeName(type));
				}
				}
				std::string sourcePortName = bind->getSourcePortIdentification()->getPortName()->getStringValue();
				connection->getPortByName("sourcePort")->connectPort(bootstrapStringValue(sourcePortName)->getDefaultPort());

				type = bind->getDestinationPortIdentification()->getComponent()->getNodeType();
				switch(type) {
				case type_node::SYMBOL : {
					std::string destinationComponentName = cast(ast_symbol)(bind->getDestinationPortIdentification()->getComponent())->getStringValue();
					connection->getPortByName("destinationComponent")->connectPort(bootstrapStringValue(destinationComponentName)->getDefaultPort());
					connection->getPortByName("destinationType")->connectPort(bootstrapStringValue(CONNECTION_NAMED)->getDefaultPort());
					break;
				}
				case type_node::SERVICE_INVOCATION : {
					connection->getPortByName("destinationComponentInvocation")->connectPort(
					    bootstrapServiceInvocationComponent(cast(ast_serviceinvocation)(bind->getDestinationPortIdentification()->getComponent()), connection)
					    ->getPortByName("default"));
					connection->getPortByName("destinationType")->connectPort(bootstrapStringValue(CONNECTION_INVOCATION)->getDefaultPort());
					break;
				}
				case type_node::COLLECTION_PORT : {
					//ptr(ast_expression) expr = cast(ast_collectionportliteral)(bind->getDestinationPortIdentification()->getComponent())->getIndexExpression();
					connection->getPortByName("destinationType")->connectPort(bootstrapStringValue(CONNECTION_COLLECTION)->getDefaultPort());
					break;
				}
				case type_node::DEREFERENCE : {
					connection->getPortByName("destinationType")->connectPort(bootstrapStringValue(CONNECTION_DEREFERENCE)->getDefaultPort());
					break;
				}
				default : {
					throw exceptions::runtime::CUnknownAstNodeTypeException(typeName(type));
				}
				}
				std::string destinationPortName = bind->getDestinationPortIdentification()->getPortName()->getStringValue();
				connection->getPortByName("destinationPort")->connectPort(bootstrapStringValue(destinationPortName)->getDefaultPort());

				bool isDisconnection = bind->getNodeType() == types::nodeType::DISCONNECTION;
				connection->getPortByName("isDisconnection")->connectPort(bootstrapBoolValue(isDisconnection)->getDefaultPort());

				servicesNames.at("setSourceType")->setCallback(prepareStringSetter("sourceType"));
				servicesNames.at("getSourceType")->setCallback(prepareStringGetter("sourceType"));
				servicesNames.at("setSourceComponent")->setCallback(prepareStringSetter("sourceComponent"));
				servicesNames.at("getSourceComponent")->setCallback(prepareStringGetter("sourceComponent"));
				servicesNames.at("setSourcePort")->setCallback(prepareStringSetter("sourcePort"));
				servicesNames.at("getSourcePort")->setCallback(prepareStringGetter("sourcePort"));

				servicesNames.at("setDestinationType")->setCallback(prepareStringSetter("destinationType"));
				servicesNames.at("getDestinationType")->setCallback(prepareStringGetter("destinationType"));
				servicesNames.at("setDestinationComponent")->setCallback(prepareStringSetter("destinationComponent"));
				servicesNames.at("getDestinationComponent")->setCallback(prepareStringGetter("destinationComponent"));
				servicesNames.at("setDestinationPort")->setCallback(prepareStringSetter("destinationPort"));
				servicesNames.at("getDestinationPort")->setCallback(prepareStringGetter("destinationPort"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_bool) boolComponent = cast(mem_bool)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("isDisconnection")->disconnectPortAt(0);
					context->getPortByName("isDisconnection")->connectPort(boolComponent->getDefaultPort());
					return nullptr;
				};
				servicesNames.at("setIsDisconnection")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_port) port = context->getPortByName("isDisconnection");
					port = port->getConnectedPortAt(0);
					port = port->getOwner()->getPortByName("default");

					return port;
				};
				servicesNames.at("isDisconnection")->setCallback(callback);

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("sourceComponentIndex")->connectPort(bootstrapIntValue(index)->getDefaultPort());
					return nullptr;
				};
				servicesNames.at("setSourceComponentIndex")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_int)(context->getPortByName("sourceComponentIndex")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames.at("getSourceComponentIndex")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner()->getBottomChild();
					if (!invocation.use_count()) {
						invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					}
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("sourceComponentInvocation")->disconnectPortAt(0);
					context->getPortByName("sourceComponentInvocation")->connectPort(invocation->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("setSourceComponentInvocation")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getSourceComponentInvocation")->setCallback(callback);

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("destinationComponentIndex")->connectPort(bootstrapIntValue(index)->getDefaultPort());
					return nullptr;
				};
				servicesNames.at("setDestinationComponentIndex")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_int)(context->getPortByName("destinationComponentIndex")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames.at("getDestinationComponentIndex")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner()->getBottomChild();
					if (!invocation.use_count()) {
						invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					}
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("destinationComponentInvocation")->disconnectPortAt(0);
					context->getPortByName("destinationComponentInvocation")->connectPort(invocation->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("setDestinationComponentInvocation")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("destinationComponentInvocation")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getDestinationComponentInvocation")->setCallback(callback);

				bootstrapEpilogue(connection, servicesNames);
				return connection;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapInterfaceComponent(ptr(mem_component) owner) {
				std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
				ptr(mem_component) interface = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Interface"), servicesNames, owner);

				servicesNames.at("setType")->setCallback(prepareStringSetter("type"));
				servicesNames.at("getType")->setCallback(prepareStringGetter("type"));

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 count = context->getPortByName("signatures")->getConnectedPortsNumber();

					return bootstrapIntValue(count)->getDefaultPort();
				};
				servicesNames.at("getSignaturesCount")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_SIGNATURES) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getSignatureAt");
					}
					u64 val = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					return context->getPortByName("signatures")->getConnectedPortAt(val)->getOwner()->getPortByName("default");
				};
				servicesNames.at("getSignatureAt")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_SIGNATURES) {
						throw exceptions::runtime::CWrongPortTypeException(type, "addSignature");
					}
					ptr(mem_component) signature = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("signatures")->connectPort(signature->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("addSignature")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getConnectedComponentName");
					}
					if (context->getPortByName("componentName")->getConnectedPortsNumber()) {
						return context->getPortByName("componentName")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames.at("getConnectedComponentName")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "setConnectedComponentName");
					}
					ptr(mem_string) component = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("componentName")->disconnectPortAt(0);
					context->getPortByName("componentName")->connectPort(component->getDefaultPort());
					return nullptr;
				};
				servicesNames.at("setConnectedComponentName")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getConnectedComponent");
					}
					if (context->getPortByName("component")->getConnectedPortsNumber()) {
						return context->getPortByName("component")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames.at("getConnectedComponent")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "setConnectedComponent");
					}
					ptr(mem_component) component = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("component")->disconnectPortAt(0);
					context->getPortByName("component")->connectPort(component->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("setConnectedComponent")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getServiceAt");
					}

					ptr(mem_int) arg = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());

					if (context->getPortByName("services")->getConnectedPortsNumber()) {
						return context->getPortByName("services")->getConnectedPortAt(arg->getValue())->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames.at("getServiceAt")->setCallback(callback);

				callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "addService");
					}
					ptr(mem_component) service = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("services")->connectPort(service->getPortByName("default"));
					return nullptr;
				};
				servicesNames.at("addService")->setCallback(callback);

				bootstrapEpilogue(interface, servicesNames);
				return interface;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapInterfaceComponent(ptr(ast_port) astPort, ptr(mem_component) owner, ptr(mem_component) portOwner) {
				ptr(mem_component) interface = bootstrapInterfaceComponent(owner);

				std::string type;

				switch (astPort->getPortType()) {
				case types::portType::EXPLICIT_LIST : {
					type = PORT_TYPE_SIGNATURES;
					interface->getPortByName("type")->connectPort(bootstrapStringValue(type)->getDefaultPort());

					ptr(ast_signaturesport) signPort = cast(ast_signaturesport)(astPort);
					for(size_t i = 0; i < signPort->getSignaturesSize(); ++i) {
						interface->getPortByName("signatures")->connectPort(bootstrapServiceSignatureComponent(signPort->getSignatureAt(i), owner)->getPortByName("default"));

						if (portOwner.use_count()) {
							std::string serviceName = signPort->getSignatureAt(i)->getNameSymbol()->getStringValue();
							interface->getPortByName("services")->connectPort(portOwner->getServiceByName(serviceName)->getDefaultPort());
						}
					}
					break;
				}
				case types::portType::INJECTED : {
					throw exceptions::semantic::CUnsupportedFeatureException("Injection port");
					break;
				}
				case types::portType::NAMED : {
					type = PORT_TYPE_NAMED;
					interface->getPortByName("type")->connectPort(bootstrapStringValue(type)->getDefaultPort());

					ptr(ast_namedport) namedPort = cast(ast_namedport)(astPort);
					interface->getPortByName("componentName")->connectPort(bootstrapStringValue(namedPort->getComponentName()->getStringValue())->getDefaultPort());
					break;
				}
				case types::portType::UNIVERSAL : {
					type = PORT_TYPE_UNIVERSAL;
					interface->getPortByName("type")->connectPort(bootstrapStringValue(type)->getDefaultPort());

					if (portOwner.use_count()) {
						portOwner->connectAllServicesTo(interface->getPortByName("services"));
					}

					break;
				}
				default : {
					throw exceptions::runtime::CUnknownPortTypeException();
				}
				}

				return interface;
			}
		}

	}
}