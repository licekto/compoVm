#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/values/unsignedIntegerComponent.h"

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

				ptr(memory::objects::primitives::CPrimitivePort) primPort = new_ptr(memory::objects::primitives::CPrimitivePort)(name, component);

				ptr(memory::objects::CGeneralPort) generalPort = new_ptr(memory::objects::CGeneralPort)(primPort, visibility, role);

				component->addPort(generalPort);
			}
                }

                void CBootstrap::addDefaultPort(std::shared_ptr<memory::objects::values::CValueComponent> value) {
                    ptr(memory::objects::primitives::CPrimitivePort) primitivePort = new_ptr(memory::objects::primitives::CPrimitivePort)("default", value);
                    ptr(memory::objects::CGeneralPort) generalPort = new_ptr(memory::objects::CGeneralPort)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
                    
                    value->addDefaultPort(generalPort);
                }

                ptr(memory::objects::values::CUnsignedIntegerComponent) CBootstrap::bootstrapValue(u64 value) {
                    ptr(memory::objects::values::CUnsignedIntegerComponent) component = new_ptr(memory::objects::values::CUnsignedIntegerComponent)(value);
                    addDefaultPort(component);
                    return component;
                }
                
                ptr(memory::objects::values::CStringComponent) CBootstrap::bootstrapValue(const std::string& value) {
                    ptr(memory::objects::values::CStringComponent) component = new_ptr(memory::objects::values::CStringComponent)(value);
                    addDefaultPort(component);
                    return component;
                }
                
                ptr(memory::objects::values::CBoolComponent) CBootstrap::bootstrapValue(bool value) {
                    ptr(memory::objects::values::CBoolComponent) component = new_ptr(memory::objects::values::CBoolComponent)(value);
                    addDefaultPort(component);
                    return component;
                }
                
		ptr(memory::objects::CComponent) CBootstrap::bootstrapComponent() {
			ptr(ast_descriptor) componentDescriptor = m_coreModules->getCoreDescriptor("Component");
			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();

			std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
			addPrimitivePorts(component, componentDescriptor);
			addPrimitiveServices(component, componentDescriptor, servicesNames);

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;

                        callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				return nullptr;
			};
			servicesNames.at("getPorts")->setCallback(callback);
                        
			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				ptr(memory::objects::values::CStringComponent) name =
				    cast(memory::objects::values::CStringComponent)(context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0)->getOwner());

                                context->getPortByName("args")->getPrimitivePort()->disconnect(0);
                                
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

			ptr(interpreter::memory::objects::primitives::CPrimitivePort) defaultPort = component->getPortByName("default")->getPrimitivePort();
			ptr(interpreter::memory::objects::primitives::CPrimitivePort) selfPort = component->getPortByName("self")->getPrimitivePort();

			for(auto const &record : servicesNames) {
				defaultPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
				selfPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
			}

			return component;
		}

		std::function<std::shared_ptr<memory::objects::CComponent>(const std::vector<std::shared_ptr<memory::objects::CComponent> >&, const std::shared_ptr<memory::objects::CComponent>&)>
		CBootstrap::prepareSymbolSetter(const std::string& portName) {

			return [&portName](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) paramComponent = context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();

				ptr(memory::objects::values::CStringComponent) param = cast(memory::objects::values::CStringComponent)(paramComponent);

				context->getPortByName(portName)->getPrimitivePort()->disconnect(0);
				context->getPortByName(portName)->getPrimitivePort()->connectPort(param->getDefaultPort());
				return nullptr;
			};
		}

		std::function<std::shared_ptr<memory::objects::CComponent>(const std::vector<std::shared_ptr<memory::objects::CComponent> >&, const std::shared_ptr<memory::objects::CComponent>&)>
		CBootstrap::prepareSymbolGetter(const std::string& portName) {
			return [&portName](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName(portName)->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
			};
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner) {
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Port");
			ptr(memory::objects::CComponent) port = bootstrapComponent();

			std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
			addPrimitivePorts(port, descriptor);
			addPrimitiveServices(port, descriptor, servicesNames);

			std::string name = astPort->getNameSymbol()->getStringValue();

			ptr(memory::objects::values::CStringComponent) nameComponent = bootstrapValue(name);
			port->getPortByName("name")->getPrimitivePort()->connectPort(nameComponent->getDefaultPort());
			port->getPortByName("owner")->getPrimitivePort()->connectPort(owner->getPortByName("default"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback;
			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("name")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getName")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("interfaceDescription")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getInterface")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) calleeComponent = context->getPortByName("owner")->getPrimitivePort()->
				        getConnectedPortAt(0)->getOwner();

				ptr(memory::objects::CComponent) argComponent = calleeComponent->getPortByName("args")->
				        getPrimitivePort()->getConnectedPortAt(0)->getOwner();
				ptr(memory::objects::values::CStringComponent) stringComponent = cast(memory::objects::values::CStringComponent)(argComponent);
				std::string serviceName = stringComponent->getValue();

				ptr(memory::objects::primitives::CPrimitiveService) primitiveService = calleeComponent->getServiceByName(serviceName)->getPrimitiveService();

				ptr(memory::objects::CGeneralPort) generalPort = calleeComponent->getPortOfService(primitiveService->getName());

				//if (generalPort->getRole())
				return nullptr;
			};
			servicesNames.at("invoke")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				bool connected = context->getPortByName("connectedPorts")->getPrimitivePort()->getConnectedPortsNumber() > 0;
				return new_ptr(memory::objects::values::CBoolComponent)(connected);
			};
			servicesNames.at("isConnected")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent) {
				// no delegation in the first stage
				return new_ptr(memory::objects::values::CBoolComponent)(false);
			};
			servicesNames.at("isDelegated")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				context->getPortByName("connectedPorts")->getPrimitivePort()->connectPort(context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0));
				return nullptr;
			};
			servicesNames.at("connectTo")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				context->getPortByName("connectedPorts")->getPrimitivePort()->disconnect(0);
				return nullptr;
			};
			servicesNames.at("disconnect")->setCallback(callback);

			ptr(interpreter::memory::objects::primitives::CPrimitivePort) defaultPort = port->getPortByName("default")->getPrimitivePort();
			ptr(interpreter::memory::objects::primitives::CPrimitivePort) selfPort = port->getPortByName("self")->getPrimitivePort();

			for(auto const &record : servicesNames) {
				defaultPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
				selfPort->connectService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
			}

			return port;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context) {
			ptr(memory::objects::CComponent) service = bootstrapComponent();

			addPrimitivePorts(service, m_coreModules->getCoreDescriptor("Service"));

			service->getPortByName("context")->getPrimitivePort()->connectPort(context->getPortByName("default"));
			service->getPortByName("serviceSign")->getPrimitivePort()->connectPort(bootstrapServiceSignatureComponent(astService->getSignature())->getPortByName("default"));
			service->getPortByName("code")->getPrimitivePort()->connectPort(cast(memory::objects::values::CStringComponent)(bootstrapValue(astService->getBodyCode()))->getDefaultPort());

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> executeCallback =
			[this](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& contextComponent) -> ptr(memory::objects::CComponent) {
				if (contextComponent.use_count()) {
					ptr(memory::objects::values::CStringComponent) code =
					    cast(memory::objects::values::CStringComponent)(contextComponent->getPortByName("code")->getPrimitivePort()->getConnectedPortAt(0)->getOwner());

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
			ptr(memory::objects::CComponent) serviceSignature = bootstrapComponent();

			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("ServiceSignature");

			std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
			addPrimitivePorts(serviceSignature, descriptor);
			addPrimitiveServices(serviceSignature, descriptor, servicesNames);

			serviceSignature->getPortByName("name")->getPrimitivePort()
			->connectPort(cast(memory::objects::values::CStringComponent)(bootstrapValue(astSignature->getNameSymbol()->getStringValue()))->getDefaultPort());
			ptr(memory::objects::primitives::CPrimitivePort) paramNames = serviceSignature->getPortByName("paramNames")->getPrimitivePort();

			for(size_t i = 0; i < astSignature->getParamsSize(); ++i) {
				std::string param = cast(ast::nodes::procedural::CSymbol)(astSignature->getParamAt(i))->getStringValue();
				paramNames->connectPort(new_ptr(memory::objects::values::CStringComponent)(param)->getDefaultPort());
			}

			servicesNames.at("setSelector")->setCallback(prepareSymbolSetter("name"));
			servicesNames.at("getSelector")->setCallback(prepareSymbolGetter("name"));

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback
			= [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				u64 count = context->getPortByName("paramNames")->getPrimitivePort()->getConnectedPortsNumber();
				return new_ptr(memory::objects::values::CUnsignedIntegerComponent)(count);
			};
			servicesNames.at("getParamsCount")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::primitives::CPrimitivePort) params = context->getPortByName("paramNames")->getPrimitivePort();
				ptr(memory::objects::CComponent) indexComponent = context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();

				ptr(memory::objects::values::CUnsignedIntegerComponent) uintComponent = cast(memory::objects::values::CUnsignedIntegerComponent)(indexComponent);

				return params->getConnectedPortAt(uintComponent->getValue())->getOwner();
			};
			servicesNames.at("getParamName")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {

				ptr(memory::objects::CComponent) arg = context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
				u64 index = cast(memory::objects::values::CUnsignedIntegerComponent)(arg)->getValue();

				arg = context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(1)->getOwner();
				std::string name = cast(memory::objects::values::CStringComponent)(arg)->getValue();

				cast(memory::objects::values::CStringComponent)(context->getPortByName("paramNames")->getPrimitivePort()->getConnectedPortAt(index)->getOwner())->setValue(name);
				return nullptr;
			};
			servicesNames.at("setParamName")->setCallback(callback);

			return serviceSignature;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapPortDescriptionComponent(std::shared_ptr<ast_port> /*astPort*/) {
			ptr(memory::objects::CComponent) portDescription = bootstrapComponent();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("PortDescription");

			addPrimitivePorts(portDescription, descriptor);
                        
                        
                        
			std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
			addPrimitiveServices(portDescription, descriptor, servicesNames);

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
				ptr(memory::objects::CComponent) paramComponent = context->getPortByName("args")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
				context->getPortByName("interfaceDefinition")->getPrimitivePort()->connectPort(paramComponent->getPortByName("default"));
				return nullptr;
			};
			servicesNames.at("setInterface")->setCallback(callback);

			callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent) {
				return context->getPortByName("interfaceDefinition")->getPrimitivePort()->getConnectedPortAt(0)->getOwner();
			};
			servicesNames.at("getInterface")->setCallback(callback);
			return portDescription;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapDescriptorComponent() {
//			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
//			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Descriptor");
//
//			return component;
                        return nullptr;
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