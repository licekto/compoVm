#include "interpreter/core/bootstrap.h"

namespace interpreter {

	namespace core {

		CBootstrap::CBootstrap(std::shared_ptr<core::CCoreModules> coreModules,
		                       const ptr(core::CInterpreter)& interpreter)
			: m_coreModules(coreModules),
			  m_interpreter(interpreter) {
		}

		void CBootstrap::addPrimitiveServices(std::shared_ptr<memory::objects::CComponent> component, std::shared_ptr<ast_descriptor> descriptor,
		                                      std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)>& servicesNames) {

			for(size_t i = 0; i < descriptor->getServicesSize(); ++i) {
				ptr(ast_service) astService = descriptor->getServiceAt(i);

				std::string serviceName = astService->getNameSymbol()->getStringValue();

				ptr(memory::objects::primitives::CPrimitiveService) primitiveService =
				    new_ptr(memory::objects::primitives::CPrimitiveService)(serviceName, component);

				for (size_t j = 0; j < astService->getParamsSize(); ++j) {
					primitiveService->setArgumentName(cast(ast::nodes::procedural::CSymbol)(astService->getParamAt(j))->getStringValue());
				}

				servicesNames[serviceName] = primitiveService;
				component->addService(new_ptr(memory::objects::CGeneralService)(primitiveService));
			}

		}

		void CBootstrap::addPrimitivePorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor) {
			for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
				ptr(ast_port) port = descriptor->getPortAt(i);

				types::visibilityType visibility = port->getVisibility();

				types::roleType role = port->getRole();

				std::string name = port->getNameSymbol()->getStringValue();

				ptr(memory::objects::primitives::CPrimitivePort) primitivePort = new_ptr(memory::objects::primitives::CPrimitivePort)(name, component);

				ptr(memory::objects::CGeneralPort) generalPort = new_ptr(memory::objects::CGeneralPort)(primitivePort, visibility, role);

				component->addPort(generalPort);
			}
		}

		void CBootstrap::addDefaultPort(std::shared_ptr<memory::objects::values::CValueComponent> value) {
			ptr(memory::objects::primitives::CPrimitivePort) primitivePort = new_ptr(memory::objects::primitives::CPrimitivePort)("default", value);
			ptr(memory::objects::CGeneralPort) generalPort = new_ptr(memory::objects::CGeneralPort)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
			value->addDefaultPort(generalPort);
                }

                std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapPrologue(std::shared_ptr<ast_descriptor> descriptor,
                                                                                           std::map<std::string,std::shared_ptr<memory::objects::primitives::CPrimitiveService> >& servicesNames) {
			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
			addPrimitivePorts(component, descriptor);
			addPrimitiveServices(component, descriptor, servicesNames);
                        return component;
                }
                
                void CBootstrap::bootstrapEpilogue(std::shared_ptr<memory::objects::CComponent> component,
                                                   std::map<std::string,std::shared_ptr<memory::objects::primitives::CPrimitiveService> >& servicesNames) {
                        ptr(interpreter::memory::objects::primitives::CPrimitivePort) defaultPort = component->getPortByName("default")->getPrimitivePort();
			ptr(interpreter::memory::objects::primitives::CPrimitivePort) selfPort = component->getPortByName("self")->getPrimitivePort();

			for(auto const &record : servicesNames) {
				defaultPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
				selfPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
			}
                }

		ptr(memory::objects::values::CUnsignedIntegerComponent) CBootstrap::bootstrapUIntValue(u64 value) {
			ptr(memory::objects::values::CUnsignedIntegerComponent) component = new_ptr(memory::objects::values::CUnsignedIntegerComponent)(value);
			addDefaultPort(component);
			return component;
		}

		ptr(memory::objects::values::CStringComponent) CBootstrap::bootstrapStringValue(const std::string& value) {
			ptr(memory::objects::values::CStringComponent) component = new_ptr(memory::objects::values::CStringComponent)(value);
			addDefaultPort(component);
			return component;
		}

		ptr(memory::objects::values::CBoolComponent) CBootstrap::bootstrapBoolValue(bool value) {
			ptr(memory::objects::values::CBoolComponent) component = new_ptr(memory::objects::values::CBoolComponent)(value);
			addDefaultPort(component);
			return component;
		}

		std::function<std::shared_ptr<memory::objects::CComponent>(const std::vector<std::shared_ptr<memory::objects::CComponent> >&, const std::shared_ptr<memory::objects::CComponent>&)>
		CBootstrap::prepareSymbolSetter(const std::string& portName) {

			return [&portName](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

				context->getPortByName("args")->disconnectPortAt(0);

				ptr(memory::objects::values::CStringComponent) param = cast(memory::objects::values::CStringComponent)(paramComponent);

				context->getPortByName(portName)->disconnectPortAt(0);
				context->getPortByName(portName)->connectPort(param->getDefaultPort());
				return nullptr;
			};
		}

		std::function<std::shared_ptr<memory::objects::CComponent>(const std::vector<std::shared_ptr<memory::objects::CComponent> >&, const std::shared_ptr<memory::objects::CComponent>&)>
		CBootstrap::prepareSymbolGetter(const std::string& portName) {
			return [&portName](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName(portName)->getConnectedPortAt(0)->getOwner();
			};
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapComponent() {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) component = bootstrapPrologue(m_coreModules->getCoreDescriptor("Component"), servicesNames);

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				return nullptr;
			};
			servicesNames.at("getPorts")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::values::CStringComponent) name =
				    cast(memory::objects::values::CStringComponent)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());

				context->getPortByName("args")->disconnectPortAt(0);

				ptr(memory::objects::CGeneralPort) port = context->getPortByName(name->getValue());

				if (!port->isPrimitive()) {
					return port->getPort();
				} else {
					// throw
					return nullptr;
				}
			};
			servicesNames.at("getPortNamed")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				return nullptr;
			};
			servicesNames.at("getDescriptor")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context;
			};
			servicesNames.at("getOwner")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				//return new_ptr(memory::objects::CUnsignedIntComponent)(std::hash<memory::objects::CComponent>()(context.get()));
				return 0;
			};
			servicesNames.at("getIdentityHash")->setCallback(callback);

                        bootstrapEpilogue(component, servicesNames);
			return component;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner) {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) port = bootstrapPrologue(m_coreModules->getCoreDescriptor("Port"), servicesNames);

			std::string name = astPort->getNameSymbol()->getStringValue();

			ptr(memory::objects::values::CStringComponent) nameComponent = bootstrapStringValue(name);
			port->getPortByName("name")->connectPort(nameComponent->getDefaultPort());
			port->getPortByName("owner")->connectPort(owner->getPortByName("default"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;
			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("name")->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getName")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getInterface")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) calleeComponent = context->getPortByName("owner")->getConnectedPortAt(0)->getOwner();

				ptr(memory::objects::CComponent) argComponent = calleeComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				ptr(memory::objects::values::CStringComponent) stringComponent = cast(memory::objects::values::CStringComponent)(argComponent);
				std::string serviceName = stringComponent->getValue();

				context->getPortByName("args")->disconnectPortAt(0);

				ptr(memory::objects::primitives::CPrimitiveService) primitiveService = calleeComponent->getServiceByName(serviceName)->getPrimitiveService();

				ptr(memory::objects::CGeneralPort) generalPort = calleeComponent->getPortOfService(primitiveService->getName());

				//if (generalPort->getRole())
				return nullptr;
			};
			servicesNames.at("invoke")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				bool connected = context->getPortByName("connectedPorts")->getConnectedPortsNumber() > 0;
				return new_ptr(memory::objects::values::CBoolComponent)(connected);
			};
			servicesNames.at("isConnected")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				// no delegation in the first stage
				return new_ptr(memory::objects::values::CBoolComponent)(false);
			};
			servicesNames.at("isDelegated")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				context->getPortByName("connectedPorts")->connectPort(context->getPortByName("args")->getConnectedPortAt(0));
				context->getPortByName("args")->disconnectPortAt(0);
				return nullptr;
			};
			servicesNames.at("connectTo")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				context->getPortByName("connectedPorts")->disconnectPortAt(0);
				return nullptr;
			};
			servicesNames.at("disconnect")->setCallback(callback);

                        bootstrapEpilogue(port, servicesNames);
			return port;
                }

                std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapCollectionPortComponent(std::shared_ptr<ast_port> astPort, std::shared_ptr<memory::objects::CComponent> owner) {
                        ptr(memory::objects::CComponent) port = bootstrapPortComponent(astPort, owner);
                        
                        port->removeServiceByName("invoke");
                        port->removeServiceByName("disconnect");
                        
                        std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;
			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
                                ptr(memory::objects::CComponent) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				std::string name = cast(memory::objects::values::CStringComponent)(arg)->getValue();    
                            
                                arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
				u64 index = cast(memory::objects::values::CUnsignedIntegerComponent)(arg)->getValue();

				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("args")->disconnectPortAt(1);

				cast(memory::objects::values::CStringComponent)(context->getPortByName("paramNames")->getConnectedPortAt(index)->getOwner())->setValue(name);
				return nullptr;
			};
                        std::vector<std::string> argumentsNames;
                        argumentsNames.push_back("name");
                        argumentsNames.push_back("index");
                        ptr(memory::objects::CGeneralService) srv = new_ptr(memory::objects::CGeneralService)(new_ptr(memory::objects::primitives::CPrimitiveService)("invoke", port, callback, argumentsNames));
                        port->addService(srv);
                        port->getPortByName("default")->getPrimitivePort()->connectService(srv);
                        port->getPortByName("self")->getPrimitivePort()->connectService(srv);
                                                
                        callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				u64 val = cast(memory::objects::values::CUnsignedIntegerComponent)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
				context->getPortByName("connectedPorts")->disconnectPortAt(val);
				return nullptr;
			};
                        srv = new_ptr(memory::objects::CGeneralService)(new_ptr(memory::objects::primitives::CPrimitiveService)("disconnect", port, callback));
                        port->addService(srv);
                        port->getPortByName("default")->getPrimitivePort()->connectService(srv);
                        port->getPortByName("self")->getPrimitivePort()->connectService(srv);
                        
                        return port;
                }

		ptr(memory::objects::CComponent) CBootstrap::bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context) {
			ptr(memory::objects::CComponent) service = bootstrapComponent();

			addPrimitivePorts(service, m_coreModules->getCoreDescriptor("Service"));

			service->getPortByName("context")->connectPort(context->getPortByName("default"));
			service->getPortByName("serviceSign")->connectPort(bootstrapServiceSignatureComponent(astService->getSignature())->getPortByName("default"));
			service->getPortByName("code")->connectPort(cast(memory::objects::values::CStringComponent)(bootstrapStringValue(astService->getBodyCode()))->getDefaultPort());

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> executeCallback =
			[this](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& contextComponent) -> ptr(memory::objects::CComponent) {
				if (contextComponent.use_count()) {
					ptr(memory::objects::values::CStringComponent) code =
					    cast(memory::objects::values::CStringComponent)(contextComponent->getPortByName("code")->getConnectedPortAt(0)->getOwner());

					m_interpreter->execService(code->getValue());
				}
				return nullptr;
			};

			ptr(memory::objects::CGeneralService) executeService =
			    new_ptr(memory::objects::CGeneralService)(new_ptr(memory::objects::primitives::CPrimitiveService)("execute", service, executeCallback));

			service->addService(executeService);

			service->getPortByName("default")->getPrimitivePort()->connectService(executeService);
			service->getPortByName("self")->getPrimitivePort()->connectService(executeService);

			return service;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature) {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) serviceSignature = bootstrapPrologue(m_coreModules->getCoreDescriptor("ServiceSignature"), servicesNames);

			serviceSignature->getPortByName("name")->
                            connectPort(cast(memory::objects::values::CStringComponent)(bootstrapStringValue(astSignature->getNameSymbol()->getStringValue()))->getDefaultPort());
                        
			ptr(memory::objects::CGeneralPort) paramNames = serviceSignature->getPortByName("paramNames");

			for(size_t i = 0; i < astSignature->getParamsSize(); ++i) {
				std::string param = cast(ast::nodes::procedural::CSymbol)(astSignature->getParamAt(i))->getStringValue();
				paramNames->connectPort(new_ptr(memory::objects::values::CStringComponent)(param)->getDefaultPort());
			}

			servicesNames.at("setSelector")->setCallback(prepareSymbolSetter("name"));
			servicesNames.at("getSelector")->setCallback(prepareSymbolGetter("name"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback
			= [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				u64 count = context->getPortByName("paramNames")->getConnectedPortsNumber();
				return new_ptr(memory::objects::values::CUnsignedIntegerComponent)(count);
			};
			servicesNames.at("getParamsCount")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CGeneralPort) params = context->getPortByName("paramNames");
				ptr(memory::objects::CComponent) indexComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

				context->getPortByName("args")->disconnectPortAt(0);

				ptr(memory::objects::values::CUnsignedIntegerComponent) uintComponent = cast(memory::objects::values::CUnsignedIntegerComponent)(indexComponent);

				return params->getConnectedPortAt(uintComponent->getValue())->getOwner();
			};
			servicesNames.at("getParamName")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				u64 index = cast(memory::objects::values::CUnsignedIntegerComponent)(arg)->getValue();

				arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
				std::string name = cast(memory::objects::values::CStringComponent)(arg)->getValue();

				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("args")->disconnectPortAt(1);

				cast(memory::objects::values::CStringComponent)(context->getPortByName("paramNames")->getConnectedPortAt(index)->getOwner())->setValue(name);
				return nullptr;
			};
			servicesNames.at("setParamName")->setCallback(callback);

                        bootstrapEpilogue(serviceSignature, servicesNames);
			return serviceSignature;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapPortDescriptionComponent(std::shared_ptr<ast_port> astPort) {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) portDescription = bootstrapPrologue(m_coreModules->getCoreDescriptor("PortDescription"), servicesNames);

			portDescription->getPortByName("name")->connectPort(bootstrapStringValue(astPort->getNameSymbol()->getStringValue())->getDefaultPort());
			std::string role = astPort->getRole() == types::roleType::PROVIDES ? ROLE_PROVISION : ROLE_REQUIREMENT;
			portDescription->getPortByName("role")->connectPort(bootstrapStringValue(role)->getDefaultPort());
			std::string visibility = astPort->getVisibility() == types::visibilityType::EXTERNAL ? VISIBILITY_EXTERNAL : VISIBILITY_INTERNAL;
			portDescription->getPortByName("visibility")->connectPort(bootstrapStringValue(visibility)->getDefaultPort());
			portDescription->getPortByName("kind")->connectPort(bootstrapStringValue(astPort->getKindOf()->getStringValue())->getDefaultPort());
			portDescription->getPortByName("isCollectionPort")->connectPort(bootstrapBoolValue(astPort->isCollection())->getDefaultPort());

			portDescription->getPortByName("interfaceDefinition")->connectPort(bootstrapInterfaceComponent(astPort)->getPortByName("default"));

			servicesNames.at("setName")->setCallback(prepareSymbolSetter("name"));
			servicesNames.at("getName")->setCallback(prepareSymbolGetter("name"));

			servicesNames.at("setRole")->setCallback(prepareSymbolSetter("role"));
			servicesNames.at("getRole")->setCallback(prepareSymbolGetter("role"));

			servicesNames.at("setKind")->setCallback(prepareSymbolSetter("kind"));
			servicesNames.at("getKind")->setCallback(prepareSymbolGetter("kind"));

			servicesNames.at("setVisibility")->setCallback(prepareSymbolSetter("visibility"));
			servicesNames.at("getVisibility")->setCallback(prepareSymbolGetter("visibility"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::CComponent) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("interfaceDefinition")->connectPort(paramComponent->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("setInterface")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getInterface")->setCallback(callback);

                        bootstrapEpilogue(portDescription, servicesNames);
			return portDescription;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind) {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) connection = bootstrapPrologue(m_coreModules->getCoreDescriptor("ConnectionDescription"), servicesNames);

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

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::values::CBoolComponent) boolComponent =
				    cast(memory::objects::values::CBoolComponent)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
				context->getPortByName("args")->disconnectPortAt(0);

				context->getPortByName("isDisconnection")->connectPort(boolComponent->getDefaultPort());
				return nullptr;
			};
			servicesNames.at("setIsDisconnection")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("isDisconnection")->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("isDisconnection")->setCallback(callback);

                        bootstrapEpilogue(connection, servicesNames);
			return connection;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapInterfaceComponent(std::shared_ptr<ast_port> astPort) {
                        std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                        ptr(memory::objects::CComponent) interface = bootstrapPrologue(m_coreModules->getCoreDescriptor("Interface"), servicesNames);

			switch (astPort->getPortType()) {
			case types::portType::EXPLICIT_LIST : {
				interface->getPortByName("type")->connectPort(bootstrapStringValue(PORT_TYPE_SIGNATURES)->getDefaultPort());
				ptr(ast_signaturesport) signPort = cast(ast_signaturesport)(astPort);

				for(size_t i = 0; i < signPort->getSignaturesSize(); ++i) {
					interface->getPortByName("signatures")->connectPort(bootstrapServiceSignatureComponent(signPort->getSignatureAt(i))->getPortByName("default"));
				}

				break;
			}
			case types::portType::INJECTED : {
				// throw unsupported feature
				break;
			}
			case types::portType::NAMED : {
				interface->getPortByName("type")->connectPort(bootstrapStringValue(PORT_TYPE_NAMED)->getDefaultPort());

				ptr(ast_namedport) namedPort = cast(ast_namedport)(astPort);

				interface->getPortByName("connectedComponent")->connectPort(bootstrapStringValue(namedPort->getComponentName()->getStringValue())->getDefaultPort());
				break;
			}
			case types::portType::UNIVERSAL : {
				interface->getPortByName("type")->connectPort(bootstrapStringValue(PORT_TYPE_UNIVERSAL)->getDefaultPort());
				break;
			}
			}

			servicesNames.at("setType")->setCallback(prepareSymbolSetter("type"));
			servicesNames.at("getType")->setCallback(prepareSymbolGetter("type"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;

			callback = [this](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				u64 count = context->getPortByName("signatures")->getConnectedPortsNumber();

				return bootstrapUIntValue(count);
			};
			servicesNames.at("getSignaturesCount")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				u64 val = cast(memory::objects::values::CUnsignedIntegerComponent)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
				context->getPortByName("args")->disconnectPortAt(0);
				return context->getPortByName("signatures")->getConnectedPortAt(val)->getOwner();
			};
			servicesNames.at("getSignaturesAt")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::CComponent) signature = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("signatures")->connectPort(signature->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("setSignatures")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("connectedComponent")->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getConnectedComponent")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::CComponent) component = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
				context->getPortByName("args")->disconnectPortAt(0);
				context->getPortByName("connectedComponent")->connectPort(component->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("setConnectedComponent")->setCallback(callback);

                        bootstrapEpilogue(interface, servicesNames);
			return interface;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapDescriptorComponent() {
			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Descriptor");
                        
                        
                        
			return component;
		}

		void CBootstrap::boostrap() {
			if (m_coreModules.use_count()) {
				m_coreModules->loadCoreModules();
				m_coreComponentsMap[core::coreModuleType::COMPONENT] = bootstrapComponent();
			}
		}

		ptr(memory::objects::CComponent) CBootstrap::getCoreComponent(core::coreModuleType type) {
			return m_coreComponentsMap[type];
		}

	}
}