#include "interpreter/core/bootstrap.h"

namespace interpreter {

	namespace core {

		CBootstrap::CBootstrap(ptr(core::CCoreModules) coreModules)
			: m_coreModules(coreModules) {
                        m_coreModules->loadCoreModules();
		}

		void CBootstrap::addPrimitiveServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor,
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

		void CBootstrap::addPrimitivePorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
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

		void CBootstrap::addDefaultPort(ptr(mem_value) value) {
			ptr(mem_primitiveport) primitivePort = new_ptr(mem_primitiveport)("default", value);
			ptr(mem_port) generalPort = new_ptr(mem_port)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
			value->addDefaultPort(generalPort);
                }

                ptr(mem_component) CBootstrap::bootstrapPrologueWithComponent(ptr(ast_descriptor) descriptor,
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
                
                ptr(mem_component) CBootstrap::bootstrapPrologue(ptr(ast_descriptor) descriptor,
                                                                                           std::map<std::string,ptr(mem_primitiveservice)>& servicesNames) {
			ptr(mem_component) component = new_ptr(mem_component)();
			addPrimitivePorts(component, descriptor);
			addPrimitiveServices(component, descriptor, servicesNames);
                        return component;
                }
                
                void CBootstrap::bootstrapEpilogue(ptr(mem_component) component,
                                                   std::map<std::string,ptr(mem_primitiveservice) >& servicesNames) {
                        ptr(mem_primitiveport) defaultPort = component->getPortByName("default")->getPrimitivePort();
			ptr(mem_primitiveport) selfPort = component->getPortByName("self")->getPrimitivePort();

			for(auto const &record : servicesNames) {
				defaultPort->connectService(new_ptr(mem_service)(record.second));
				selfPort->connectService(new_ptr(mem_service)(record.second));
			}
                }

                void CBootstrap::addPorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
                    for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
                        ptr(ast_port) port = descriptor->getPortAt(i);
                        if (port->getNameSymbol()->getStringValue() == "default") {
                            continue;
                        }
                        std::string name = port->getNameSymbol()->getStringValue();
                        component->addPort(new_ptr(mem_port)(bootstrapPortComponent(port, component), port->getVisibility(), port->getRole()));
                    }
                }

                void CBootstrap::addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
                    for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
                        component->addService(new_ptr(mem_service)(bootstrapServiceComponent(descriptor->getServiceAt(i), component)));
                    }
                }

		ptr(mem_uint) CBootstrap::bootstrapUIntValue(u64 value) {
			ptr(mem_uint) component = new_ptr(mem_uint)(value);
			addDefaultPort(component);
			return component;
		}

		ptr(mem_string) CBootstrap::bootstrapStringValue(const std::string& value) {
			ptr(mem_string) component = new_ptr(mem_string)(value);
			addDefaultPort(component);
			return component;
		}

		ptr(mem_bool) CBootstrap::bootstrapBoolValue(bool value) {
			ptr(mem_bool) component = new_ptr(mem_bool)(value);
			addDefaultPort(component);
			return component;
		}

		std::function<ptr(mem_port)(const std::vector<ptr(mem_component) >&, const ptr(mem_component)&)>
		CBootstrap::prepareSymbolSetter(const std::string& portName) {

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
		CBootstrap::prepareSymbolGetter(const std::string& portName) {
			return [portName](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
				return context->getPortByName(portName)->getConnectedPortAt(0)->getOwner()->getPortByName("default");
			};
		}

		ptr(mem_component) CBootstrap::bootstrapComponent(ptr(mem_component) owner) {
                        std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
                        ptr(mem_component) component = bootstrapPrologue(m_coreModules->getCoreDescriptor("Component"), servicesNames);

                        if (owner.use_count()) {
                            ptr(mem_port) port = owner->getPortByName("default");
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

			callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
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

		ptr(mem_component) CBootstrap::bootstrapPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
                        std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
                        ptr(mem_component) port = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Port"), servicesNames, owner);

			std::string name = astPort->getNameSymbol()->getStringValue();
                        
			port->getPortByName("name")->connectPort(bootstrapStringValue(name)->getDefaultPort());
                        port->getPortByName("interfaceDescription")->connectPort(bootstrapInterfaceComponent(astPort, port, owner)->getPortByName("default"));
                        
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

                ptr(mem_component) CBootstrap::bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
                        ptr(mem_component) port = bootstrapPortComponent(astPort, owner);
                        
                        port->removeServiceByName("invoke");
                        port->removeServiceByName("disconnectPort");
                        port->removeServiceByName("connectTo");
                        
                        std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;
			callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				std::string name = cast(mem_string)(arg)->getValue();    
                            
                                arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
				u64 index = cast(mem_uint)(arg)->getValue();

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
				u64 val = cast(mem_uint)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
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

		ptr(mem_component) CBootstrap::bootstrapServiceComponent(ptr(ast_service) astService, ptr(mem_component) owner) {
			ptr(mem_component) service = bootstrapComponent(owner);

			addPrimitivePorts(service, m_coreModules->getCoreDescriptor("Service"));
                        
			service->getPortByName("serviceSign")->connectPort(bootstrapServiceSignatureComponent(astService->getSignature(), owner)->getPortByName("default"));
			service->getPortByName("code")->connectPort(cast(mem_string)(bootstrapStringValue(astService->getBodyCode()))->getDefaultPort());

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> executeCallback =
			[this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
//				if (contextComponent.use_count()) {
//					ptr(mem_string) code = cast(mem_string)(contextComponent->getPortByName("code")->getConnectedPortAt(0)->getOwner());
//
//					m_interpreter->execService(code->getValue());
//				}
				return nullptr;
			};

			ptr(mem_service) executeService = new_ptr(mem_service)(new_ptr(mem_primitiveservice)("execute", service, executeCallback));

			service->addService(executeService);

			service->getPortByName("default")->getPrimitivePort()->connectService(executeService);
			service->getPortByName("self")->getPrimitivePort()->connectService(executeService);

			return service;
		}

		ptr(mem_component) CBootstrap::bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature, ptr(mem_component) owner) {
                        std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
                        ptr(mem_component) serviceSignature = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ServiceSignature"), servicesNames, owner);

			serviceSignature->getPortByName("name")->connectPort(cast(mem_string)(bootstrapStringValue(astSignature->getNameSymbol()->getStringValue()))->getDefaultPort());
                        
			ptr(mem_port) paramNames = serviceSignature->getPortByName("paramNames");

			for(size_t i = 0; i < astSignature->getParamsSize(); ++i) {
				std::string param = cast(ast_symbol)(astSignature->getParamAt(i))->getStringValue();
				paramNames->connectPort(bootstrapStringValue(param)->getDefaultPort());
			}

			servicesNames.at("setSelector")->setCallback(prepareSymbolSetter("name"));
			servicesNames.at("getSelector")->setCallback(prepareSymbolGetter("name"));

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback
			= [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
				u64 count = context->getPortByName("paramNames")->getConnectedPortsNumber();
				return bootstrapUIntValue(count)->getDefaultPort();
			};
			servicesNames.at("getParamsCount")->setCallback(callback);

			callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {

				ptr(mem_port) params = context->getPortByName("paramNames");
				ptr(mem_component) indexComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

				context->getPortByName("args")->disconnectPortAt(0);

				ptr(mem_uint) uintComponent = cast(mem_uint)(indexComponent);

                                ptr(mem_port) portComp = params->getConnectedPortAt(uintComponent->getValue());
                                
				return portComp->getOwner()->getPortByName("default");
			};
			servicesNames.at("getParamName")->setCallback(callback);

			callback = [](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {

				ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				u64 index = cast(mem_uint)(arg)->getValue();

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

		ptr(mem_component) CBootstrap::bootstrapPortDescriptionComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
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

			servicesNames.at("setName")->setCallback(prepareSymbolSetter("name"));
			servicesNames.at("getName")->setCallback(prepareSymbolGetter("name"));

			servicesNames.at("setRole")->setCallback(prepareSymbolSetter("role"));
			servicesNames.at("getRole")->setCallback(prepareSymbolGetter("role"));

			servicesNames.at("setKind")->setCallback(prepareSymbolSetter("kind"));
			servicesNames.at("getKind")->setCallback(prepareSymbolGetter("kind"));

			servicesNames.at("setVisibility")->setCallback(prepareSymbolSetter("visibility"));
			servicesNames.at("getVisibility")->setCallback(prepareSymbolGetter("visibility"));

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

		ptr(mem_component) CBootstrap::bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind, ptr(mem_component) owner) {
                        std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
                        ptr(mem_component) connection = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ConnectionDescription"), servicesNames, owner);

			std::string sourceComponentName = cast(ast_symbol)(bind->getSourcePortIdentification()->getComponent())->getStringValue();
			connection->getPortByName("sourceComponent")->connectPort(bootstrapStringValue(sourceComponentName)->getDefaultPort());
			std::string sourcePortName = bind->getSourcePortIdentification()->getPortName()->getStringValue();
			connection->getPortByName("sourcePort")->connectPort(bootstrapStringValue(sourcePortName)->getDefaultPort());

			std::string destinationComponentName = cast(ast_symbol)(bind->getDestinationPortIdentification()->getComponent())->getStringValue();
			connection->getPortByName("destinationComponent")->connectPort(bootstrapStringValue(destinationComponentName)->getDefaultPort());
			std::string destinationPortName = bind->getDestinationPortIdentification()->getPortName()->getStringValue();
			connection->getPortByName("destinationPort")->connectPort(bootstrapStringValue(destinationPortName)->getDefaultPort());

			bool isDisconnection = bind->getNodeType() == types::nodeType::DISCONNECTION;
			connection->getPortByName("isDisconnection")->connectPort(bootstrapBoolValue(isDisconnection)->getDefaultPort());

			servicesNames.at("setSourceComponent")->setCallback(prepareSymbolSetter("sourceComponent"));
			servicesNames.at("getSourceComponent")->setCallback(prepareSymbolGetter("sourceComponent"));
			servicesNames.at("setSourcePort")->setCallback(prepareSymbolSetter("sourcePort"));
			servicesNames.at("getSourcePort")->setCallback(prepareSymbolGetter("sourcePort"));

			servicesNames.at("setDestinationComponent")->setCallback(prepareSymbolSetter("destinationComponent"));
			servicesNames.at("getDestinationComponent")->setCallback(prepareSymbolGetter("destinationComponent"));
			servicesNames.at("setDestinationPort")->setCallback(prepareSymbolSetter("destinationPort"));
			servicesNames.at("getDestinationPort")->setCallback(prepareSymbolGetter("destinationPort"));

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
				return context->getPortByName("isDisconnection")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
			};
			servicesNames.at("isDisconnection")->setCallback(callback);

                        bootstrapEpilogue(connection, servicesNames);
			return connection;
		}

		ptr(mem_component) CBootstrap::bootstrapInterfaceComponent(ptr(ast_port) astPort, ptr(mem_component) owner, ptr(mem_component) portOwner) {
                        std::map<std::string, ptr(mem_primitiveservice)> servicesNames;
                        ptr(mem_component) interface = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Interface"), servicesNames, owner);

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
                                    // throw unsupported feature
                                    break;
                            }
                            case types::portType::NAMED : {
                                    type = PORT_TYPE_NAMED;
                                    interface->getPortByName("type")->connectPort(bootstrapStringValue(type)->getDefaultPort());

                                    ptr(ast_namedport) namedPort = cast(ast_namedport)(astPort);
                                    interface->getPortByName("componentName")->connectPort(bootstrapStringValue(namedPort->getComponentName()->getStringValue())->getDefaultPort());
                                    
                                    if (portOwner.use_count()) {
                                        interface->getPortByName("component")->connectPort(portOwner->getPortByName("default"));
                                    }
                                    break;
                            }
                            case types::portType::UNIVERSAL : {
                                    type = PORT_TYPE_UNIVERSAL;
                                    interface->getPortByName("type")->connectPort(bootstrapStringValue(type)->getDefaultPort());
                                    
                                    if (portOwner.use_count()) {
//                                        for (size_t i = 0; i < portOwner->getNumberOfAllServices(); ++i) {
//                                            interface->getPortByName("services")->connectPort(portOwner->getServiceAt(i)->getDefaultPort());
//                                        }
                                    }
                                    
                                    break;
                            }
                            default : {
                                // throw
                                break;
                            }
			}

			servicesNames.at("setType")->setCallback(prepareSymbolSetter("type"));
			servicesNames.at("getType")->setCallback(prepareSymbolGetter("type"));

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;

			callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
				u64 count = context->getPortByName("signatures")->getConnectedPortsNumber();

				return bootstrapUIntValue(count)->getDefaultPort();
			};
			servicesNames.at("getSignaturesCount")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_SIGNATURES) {
                                    // throw
                                    return nullptr;
                                }
				u64 val = cast(mem_uint)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
				context->getPortByName("args")->disconnectPortAt(0);
				return context->getPortByName("signatures")->getConnectedPortAt(val)->getOwner()->getPortByName("default");
			};
			servicesNames.at("getSignatureAt")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_SIGNATURES) {
                                    // throw
                                    return nullptr;
                                }
				ptr(mem_component) signature = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("signatures")->connectPort(signature->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("addSignature")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
                                }
                                if (context->getPortByName("componentName")->getConnectedPortsNumber()) {
                                    return context->getPortByName("componentName")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
                                }
                                return nullptr;
			};
			servicesNames.at("getConnectedComponentName")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
                                }
				ptr(mem_string) component = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
                                
				context->getPortByName("args")->disconnectPortAt(0);
                                context->getPortByName("componentName")->disconnectPortAt(0);
				context->getPortByName("componentName")->connectPort(component->getDefaultPort());
				return nullptr;
			};
			servicesNames.at("setConnectedComponentName")->setCallback(callback);

                        callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
                                }
                                if (context->getPortByName("component")->getConnectedPortsNumber()) {
                                    return context->getPortByName("component")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
                                }
                                return nullptr;
			};
			servicesNames.at("getConnectedComponent")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type != PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
                                }
				ptr(mem_component) component = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
                                
				context->getPortByName("args")->disconnectPortAt(0);
                                context->getPortByName("component")->disconnectPortAt(0);
				context->getPortByName("component")->connectPort(component->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("setConnectedComponent")->setCallback(callback);
                        
                        callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type == PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
                                }
                                
                                ptr(mem_uint) arg = cast(mem_uint)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
                                
                                if (context->getPortByName("services")->getConnectedPortsNumber()) {
                                    return context->getPortByName("services")->getConnectedPortAt(arg->getValue())->getOwner()->getPortByName("default");
                                }
                                return nullptr;
			};
			servicesNames.at("getServiceAt")->setCallback(callback);

			callback = [type](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
                                if (type == PORT_TYPE_NAMED) {
                                    // throw
                                    return nullptr;
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

		ptr(mem_component) CBootstrap::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
			ptr(mem_component) parentComponent = new_ptr(mem_component)();
                        ptr(mem_component) component = new_ptr(mem_component)();
                        ptr(ast_descriptor) coreComponent = m_coreModules->getCoreDescriptor("Component");
			ptr(ast_descriptor) coreDescriptor = m_coreModules->getCoreDescriptor("Descriptor");
                        
                        ptr(ast_port) port = coreComponent->getPortByName("default");
                        ptr(mem_port) generalPort = new_ptr(mem_port)(bootstrapPortComponent(port, nullptr), port->getVisibility(), port->getRole());
                        generalPort->getPort()->getPortByName("owner")->setOwner(component);
                        component->addPort(generalPort);
                        
                        addPorts(parentComponent, coreComponent);
                        addServices(parentComponent, coreComponent);
                        
                        addPorts(component, coreDescriptor);
                        addServices(component, coreDescriptor);
                        
                        component->setParent(parentComponent);
                        
                        component->getPortByName("name")->connectPort(bootstrapStringValue(descriptor->getNameSymbol()->getStringValue())->getDefaultPort());
                        
//                        for (size_t i = 0; i < component->getNumberOfAllServices(); ++i) {
//                            component->getPortByName("default")->getPort()
//                                     ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
//                                     ->getPortByName("services")->connectPort(component->getServiceAt(i)->getDefaultPort());
//                            
//                            component->getPortByName("self")->getPort()
//                                     ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
//                                     ->getPortByName("services")->connectPort(component->getServiceAt(i)->getDefaultPort());
//                        }
                        
			return component;
		}

	}
}