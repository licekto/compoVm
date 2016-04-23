#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "interpreter/core/interpreter.h"
#include "exceptions/runtime/unknownValueComponentTypeException.h"
#include "exceptions/runtime/wrongNumberOfParametersException.h"
#include "exceptions/runtime/wrongServiceInvocationParameterTypeException.h"
#include "exceptions/runtime/wrongBindTypeException.h"
#include "interpreter/memory/memspace/memory.h"
#include "exceptions/runtime/memoryNotFoundException.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			CBootstrapStage1::CBootstrapStage1(ptr(core::CCoreModules) coreModules, ptr(core::CInterpreter) interpreter, ptr(memory::memspace::CMemory) memory)
				: m_coreModules(coreModules),
				  m_interpreter(interpreter),
				  m_memory(memory) {
				if (m_coreModules.use_count()) {
					m_coreModules->loadCoreModules();
				}
				if (!m_memory.use_count()) {
					TRACE(ERROR, "Memory not found!");
				}
			}

			void CBootstrapStage1::setInterpreter(ptr(core::CInterpreter) interpreter) {
				m_interpreter = wptr(core::CInterpreter)(interpreter);
			}

			void CBootstrapStage1::addPrimitiveServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for(size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					ptr(ast_service) astService = descriptor->getServiceAt(i);
					component->addService(m_memory->newPrimitiveService(component, astService->getNameSymbol()->getStringValue()).lock());
				}
			}

			void CBootstrapStage1::addPrimitivePorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor) {
				for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
					component->addPort(m_memory->newPrimitivePort(component, descriptor->getPortAt(i)).lock());
				}
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPrologueWithComponent(ptr(ast_descriptor) descriptor, ptr(mem_component) owner) {
				ptr(mem_component) parentComponent = bootstrapComponent(owner);
				ptr(mem_component) component = bootstrapPrologue(descriptor);
				component->setParent(parentComponent);
				parentComponent->setChild(component);
				return component;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPrologue(ptr(ast_descriptor) descriptor) {
				ptr(mem_component) component = m_memory->newComponent().lock();
				addPrimitivePorts(component, descriptor);
				addPrimitiveServices(component, descriptor);
				return component;
			}

			void CBootstrapStage1::bootstrapEpilogue(ptr(mem_component) component, std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> >& servicesNames) {
				ptr(mem_primitiveport) defaultPort = component->getPortByName("default")->getPrimitivePort();
				ptr(mem_primitiveport) selfPort = component->getPortByName("self")->getPrimitivePort();

				for(auto const &record : servicesNames) {
					component->getServiceByName(record.first)->getPrimitiveService()->setCallback(record.second);
					defaultPort->connectService(component->getServiceByName(record.first));
					selfPort->connectService(component->getServiceByName(record.first));
				}
			}

			void CBootstrapStage1::addDefaultPort(ptr(mem_value) value) {
				value->addDefaultPort(m_memory->newPrimitivePort(value, "default", false, types::visibilityType::EXTERNAL, types::roleType::PROVIDES).lock());
			}

			ptr(mem_int) CBootstrapStage1::bootstrapIntValue(i64 value) {
				ptr(mem_int) component = m_memory->newIntComponent(value).lock();
				addDefaultPort(component);
				return component;
			}

			ptr(mem_string) CBootstrapStage1::bootstrapStringValue(const std::string& value) {
				ptr(mem_string) component = m_memory->newStringComponent(value).lock();
				addDefaultPort(component);
				return component;
			}

			ptr(mem_bool) CBootstrapStage1::bootstrapBoolValue(bool value) {
				ptr(mem_bool) component = m_memory->newBoolComponent(value).lock();
				addDefaultPort(component);
				return component;
			}

			std::function<ptr(mem_port)(const ptr(mem_component)&)> CBootstrapStage1::prepareStringSetter(const std::string& portName) {
				return [portName](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);

					ptr(mem_string) param = cast(mem_string)(paramComponent);
					context->getPortByName(portName)->disconnectPortAt(0);
					context->getPortByName(portName)->connectPort(param->getDefaultPort());
					return nullptr;
				};
			}

			std::function<ptr(mem_port)(const ptr(mem_component)&)> CBootstrapStage1::prepareStringGetter(const std::string& portName) {
				return [portName](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName(portName)->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
			}

			ptr(mem_component) CBootstrapStage1::bootstrapComponent(ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) component = bootstrapPrologue(m_coreModules->getCoreDescriptor("Component"));

				if (owner.use_count()) {
					ptr(mem_port) port = owner->getPortByName("default");
					if (component->getPortByName("owner")->getConnectedPortsNumber()) {
						component->getPortByName("owner")->disconnectPortAt(0);
					}
					component->getPortByName("owner")->connectPort(port);
				}

				servicesNames["getPorts"] = [](const ptr(mem_component)& /*context*/) -> ptr(mem_port) {
					//return context->getPortByName("")
					return nullptr;
				};
				servicesNames["getPortNamed"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_string) name = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
					context->getPortByName("args")->disconnectPortAt(0);
					return context->getPortByName(name->getValue());
				};
				servicesNames["getDescriptor"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					if (context->getPortByName("descriptorPort")->getConnectedPortsNumber()) {
						return context->getPortByName("descriptorPort")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames["getOwner"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					if (context->getPortByName("owner")->getConnectedPortsNumber()) {
						return context->getPortByName("owner")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames["getIdentityHash"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					return bootstrapIntValue(context->getHash())->getDefaultPort();
				};

				bootstrapEpilogue(component, servicesNames);
				return component;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				ptr(mem_component) port = bootstrapPortComponent(owner);

				std::string name = astPort->getNameSymbol()->getStringValue();

				port->getPortByName("name")->connectPort(bootstrapStringValue(name)->getDefaultPort());
				port->getPortByName("interfaceDescription")->connectPort(bootstrapInterfaceComponent(astPort, port, owner)->getPortByName("default"));
				port->getPortByName("isCollection")->connectPort(bootstrapBoolValue(false)->getDefaultPort());

				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortComponent(ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) port = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Port"), owner);

				servicesNames["getName"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("name")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames["getInterface"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames["invoke"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {

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
				servicesNames["isConnected"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					bool connected = context->getPortByName("connectedPorts")->getConnectedPortsNumber() > 0;
					return bootstrapBoolValue(connected)->getDefaultPort();
				};
				servicesNames["isDelegated"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					bool connected = context->getPortByName("delegatedPorts")->getConnectedPortsNumber() > 0;
					return bootstrapBoolValue(connected)->getDefaultPort();
				};
				servicesNames["connectTo"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->disconnectPortAt(0);
					context->getPortByName("connectedPorts")->connectPort(context->getPortByName("args")->getConnectedPortAt(0));
					context->getPortByName("args")->disconnectPortAt(0);
					return nullptr;
				};
				servicesNames["disconnectPort"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->disconnectPortAt(0);
					return nullptr;
				};
				servicesNames["isCollectionPort"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					bool collection = cast(mem_bool)(context->getPortByName("isCollection")->getConnectedPortAt(0)->getOwner())->getValue();
					return bootstrapBoolValue(collection)->getDefaultPort();
				};

				bootstrapEpilogue(port, servicesNames);
				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				ptr(mem_component) port = bootstrapCollectionPortComponent(owner);

				std::string name = astPort->getNameSymbol()->getStringValue();

				port->getPortByName("name")->connectPort(bootstrapStringValue(name)->getDefaultPort());
				port->getPortByName("interfaceDescription")->connectPort(bootstrapInterfaceComponent(astPort, port, owner)->getPortByName("default"));
				port->getPortByName("isCollection")->connectPort(bootstrapBoolValue(true)->getDefaultPort());

				return port;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapCollectionPortComponent(ptr(mem_component) owner) {
				ptr(mem_component) port = bootstrapPortComponent(owner);

				port->getPortByName("isCollection")->disconnectPortAt(0);
				port->getPortByName("isCollection")->connectPort(bootstrapBoolValue(true)->getDefaultPort());

				port->getPortByName("default")->getPrimitivePort()->disconnectServiceByName("connectTo");
				port->getPortByName("self")->getPrimitivePort()->disconnectServiceByName("connectTo");
				port->getPortByName("default")->getPrimitivePort()->disconnectServiceByName("disconnectPort");
				port->getPortByName("self")->getPrimitivePort()->disconnectServiceByName("disconnectPort");
				port->getPortByName("default")->getPrimitivePort()->disconnectServiceByName("invoke");
				port->getPortByName("self")->getPrimitivePort()->disconnectServiceByName("invoke");
				port->removeServiceByName("invoke");
				port->removeServiceByName("disconnectPort");
				port->removeServiceByName("connectTo");

				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback;
				callback = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					std::string name = cast(mem_string)(arg)->getValue();

					arg = context->getPortByName("args")->getConnectedPortAt(1)->getOwner();
					u64 index = cast(mem_int)(arg)->getValue();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("args")->disconnectPortAt(1);

					cast(mem_string)(context->getPortByName("paramNames")->getConnectedPortAt(index)->getOwner())->setValue(name);
					return nullptr;
				};
				ptr(mem_service) srv = m_memory->newPrimitiveService(port, "invoke", callback).lock();
				port->addService(srv);
				port->getPortByName("default")->getPrimitivePort()->connectService(srv);
				port->getPortByName("self")->getPrimitivePort()->connectService(srv);

				callback = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 val = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("connectedPorts")->disconnectPortAt(val);
					return nullptr;
				};
				srv = m_memory->newPrimitiveService(port, "disconnectPort", callback).lock();
				port->addService(srv);
				port->getPortByName("default")->getPrimitivePort()->connectService(srv);
				port->getPortByName("self")->getPrimitivePort()->connectService(srv);

				callback = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					context->getPortByName("connectedPorts")->connectPort(context->getPortByName("args")->getConnectedPortAt(0));
					context->getPortByName("args")->disconnectPortAt(0);
					return nullptr;
				};
				srv = m_memory->newPrimitiveService(port, "connectTo", callback).lock();
				port->addService(srv);
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
							throw exceptions::runtime::CUnknownValueComponentTypeException();
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

				std::function<ptr(mem_port)(const ptr(mem_component)&)> callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					if (contextComponent.use_count()) {
						ptr(mem_string) code = cast(mem_string)(contextComponent->getPortByName("code")->getConnectedPortAt(0)->getOwner());

						ptr(interpreter::core::CContext) context = new_ptr(interpreter::core::CContext)();

						ptr(mem_component) sign = contextComponent->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner();

						size_t paramsNumber = sign->getPortByName("paramNames")->getConnectedPortsNumber();

						ptr(mem_port) argsPort = contextComponent->getPortByName("args");
						if (paramsNumber != argsPort->getConnectedPortsNumber()) {
							if (paramsNumber == owner->getPortByName("args")->getConnectedPortsNumber()) {
								argsPort = owner->getPortByName("args");
							} else {
								ptr(mem_port) delegatedPort = contextComponent->getPortByName("args");

								while (delegatedPort->getDelegatedPort().use_count()) {
									delegatedPort = delegatedPort->getDelegatedPort();
								}
								argsPort = delegatedPort;
								if (paramsNumber != argsPort->getConnectedPortsNumber()) {
									std::string name = cast(mem_string)(
									                       contextComponent->getPortByName("serviceSign")
									                       ->getConnectedPortAt(0)->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();

									throw exceptions::runtime::CWrongNumberOfParametersException(name, argsPort->getConnectedPortsNumber());
								}
							}
						}

						for (size_t i = 0; i < paramsNumber; ++i) {
							std::string paramName = cast(mem_string)(sign->getPortByName("paramNames")->getConnectedPortAt(i)->getOwner())->getValue();
							ptr(mem_port) port = argsPort->getConnectedPortAt(i);
							context->addVariable(paramName);
							context->setVariable(paramName, port);
						}

						std::map<std::string, ptr(mem_port)> portsMap;
						if (owner.use_count()) {
							context->setContextComponent(owner);
							portsMap = owner->getAllPorts();

							for (auto item : portsMap) {
								context->addVariable(item.first);
								if (item.second->getConnectedPortsNumber()) {
									context->setPort(item.first, item.second->getConnectedPortAt(0));
								} else {
									context->setPort(item.first, item.second);
								}
							}
						}

						std::string serviceName = cast(mem_string)(sign->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
						context->setServiceName(serviceName);
						ptr(mem_port) retPort = m_interpreter.lock()->execServiceCode(code->getValue(), context);

						context->connectPorts();

						for (size_t i = 0; i < argsPort->getConnectedPortsNumber(); ++i) {
							argsPort->disconnectPortAt(i);
						}
						return retPort;
					}
					return nullptr;
				};
				ptr(mem_service) primitiveService = m_memory->newPrimitiveService(service, "execute", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					std::string name = cast(mem_string)(contextComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					contextComponent->getPortByName("args")->disconnectAll();

					if (!contextComponent->getPortByName("serviceSign")->getConnectedPortsNumber()) {
						contextComponent->getPortByName("serviceSign")->connectPort(bootstrapServiceSignatureComponent(contextComponent)->getPortByName("default"));
					}
					contextComponent->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner()->getPortByName("selector")->connectPort(bootstrapStringValue(name)->getDefaultPort());
					return nullptr;
				};
				primitiveService = m_memory->newPrimitiveService(service, "setName", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					std::string name = cast(mem_string)(contextComponent->getPortByName("serviceSign")
					                                    ->getConnectedPortAt(0)->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
					return bootstrapStringValue(name)->getDefaultPort();
				};
				primitiveService = m_memory->newPrimitiveService(service, "getName", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					std::string param = cast(mem_string)(contextComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					contextComponent->getPortByName("args")->disconnectAll();
					if (!contextComponent->getPortByName("serviceSign")->getConnectedPortsNumber()) {
						contextComponent->getPortByName("serviceSign")->connectPort(bootstrapServiceSignatureComponent(contextComponent)->getPortByName("default"));
					}
					contextComponent->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner()->getPortByName("paramNames")->connectPort(bootstrapStringValue(param)->getDefaultPort());
					return nullptr;
				};
				primitiveService = m_memory->newPrimitiveService(service, "addParam", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					i64 index = cast(mem_int)(contextComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					contextComponent->getPortByName("args")->disconnectAll();
					std::string paramName = cast(mem_string)(contextComponent->getPortByName("serviceSign")->getConnectedPortAt(0)->getOwner()->getPortByName("paramNames")
					                        ->getConnectedPortAt(index)->getOwner())->getValue();
					return bootstrapStringValue(paramName)->getDefaultPort();
				};
				primitiveService = m_memory->newPrimitiveService(service, "getParamAt", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					std::string code = cast(mem_string)(contextComponent->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					contextComponent->getPortByName("args")->disconnectAll();
					contextComponent->getPortByName("code")->disconnectAll();
					contextComponent->getPortByName("code")->connectPort(bootstrapStringValue(code)->getDefaultPort());
					return nullptr;
				};
				primitiveService = m_memory->newPrimitiveService(service, "setCode", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

				callback = [this, owner](const ptr(mem_component)& contextComponent) -> ptr(mem_port) {
					return bootstrapStringValue(cast(mem_string)(contextComponent->getPortByName("code")->getConnectedPortAt(0)->getOwner())->getValue())->getDefaultPort();
				};
				primitiveService = m_memory->newPrimitiveService(service, "getCode", callback).lock();
				service->addService(primitiveService);
				service->getPortByName("default")->getPrimitivePort()->connectService(primitiveService);
				service->getPortByName("self")->getPrimitivePort()->connectService(primitiveService);

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
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) serviceSignature = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ServiceSignature"), owner);

				servicesNames["setSelector"] = prepareStringSetter("selector");
				servicesNames["getSelector"] = prepareStringGetter("selector");

				servicesNames["getParamsCount"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 count = context->getPortByName("paramNames")->getConnectedPortsNumber();
					return bootstrapIntValue(count)->getDefaultPort();
				};
				servicesNames["getParamAt"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_port) params = context->getPortByName("paramNames");
					ptr(mem_component) indexComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					ptr(mem_int) uintComponent = cast(mem_int)(indexComponent);
					ptr(mem_port) portComp = params->getConnectedPortAt(uintComponent->getValue());
					return portComp->getOwner()->getPortByName("default");
				};
				servicesNames["setParam"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					std::string name = cast(mem_string)(arg)->getValue();
					context->getPortByName("args")->disconnectPortAt(0);

					context->getPortByName("paramNames")->connectPort(bootstrapStringValue(name)->getDefaultPort());
					return nullptr;
				};

				bootstrapEpilogue(serviceSignature, servicesNames);
				return serviceSignature;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortDescriptionComponent(ptr(ast_port) astPort, ptr(mem_component) owner) {
				ptr(mem_component) portDescription = bootstrapPortDescriptionComponent(owner);

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

				return portDescription;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapPortDescriptionComponent(ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) portDescription = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("PortDescription"), owner);

				servicesNames["setName"] = prepareStringSetter("name");
				servicesNames["getName"] = prepareStringGetter("name");

				servicesNames["setRole"] = prepareStringSetter("role");
				servicesNames["getRole"] = prepareStringGetter("role");

				servicesNames["setKind"] = prepareStringSetter("kind");
				servicesNames["getKind"] = prepareStringGetter("kind");

				servicesNames["setVisibility"] = prepareStringSetter("visibility");
				servicesNames["getVisibility"] = prepareStringGetter("visibility");

				servicesNames["setInterface"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) paramComponent = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("interfaceDefinition")->disconnectPortAt(0);
					context->getPortByName("interfaceDefinition")->connectPort(paramComponent->getPortByName("default"));
					return nullptr;
				};
				servicesNames["getInterface"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames["setIsCollection"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_bool) paramComponent = cast(mem_bool)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("isCollectionPort")->disconnectPortAt(0);
					context->getPortByName("isCollectionPort")->connectPort(paramComponent->getDefaultPort());
					return nullptr;
				};
				servicesNames["isCollection"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_bool)(context->getPortByName("isCollectionPort")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames["setType"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string typeName = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					if (!context->getPortByName("interfaceDefinition")->getConnectedPortsNumber()) {
						context->getPortByName("interfaceDefinition")->connectPort(bootstrapInterfaceComponent(context)->getPortByName("default"));
					}
					context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("type")->disconnectAll();
					context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("type")->connectPort(bootstrapStringValue(typeName)->getDefaultPort());
					return nullptr;
				};
				servicesNames["setComponentName"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string componentName = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					if (!context->getPortByName("interfaceDefinition")->getConnectedPortsNumber()) {
						context->getPortByName("interfaceDefinition")->connectPort(bootstrapInterfaceComponent(context)->getPortByName("default"));
					}
					context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("componentName")->disconnectAll();
					context->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner()->getPortByName("componentName")
					->connectPort(bootstrapStringValue(componentName)->getDefaultPort());
					return nullptr;
				};

				bootstrapEpilogue(portDescription, servicesNames);
				return portDescription;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapServiceInvocationComponent(ptr(ast_serviceinvocation) astServiceInv, ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) invocation = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ServiceInvocation"), owner);

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
							throw exceptions::runtime::CWrongServiceInvocationParameterTypeException(sign->getParamAt(i)->getNodeType());
						}
						}
					}
				} else {
					throw exceptions::runtime::CWrongServiceInvocationParameterTypeException(astServiceInv->getParameters()->getNodeType());
				}

				servicesNames["setReceiver"] = prepareStringSetter("receiver");
				servicesNames["getReceiver"] = prepareStringGetter("receiver");
				servicesNames["setSelector"] = prepareStringSetter("selector");
				servicesNames["getSelector"] = prepareStringGetter("selector");

				servicesNames["getParamsCount"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					return bootstrapIntValue(context->getPortByName("params")->getConnectedPortsNumber())->getDefaultPort();
				};
				servicesNames["getParamAt"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					u64 index = cast(mem_int)(arg)->getValue();
					return context->getPortByName("params")->getConnectedPortAt(index)->getOwner()->getPortByName("default");
				};
				servicesNames["addParam"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) arg = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("params")->connectPort(arg->getPortByName("default"));
					return nullptr;
				};

				bootstrapEpilogue(invocation, servicesNames);
				return invocation;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind, ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) connection = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("ConnectionDescription"), owner);

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

				std::string bindType;
				if (bind->getNodeType() == types::nodeType::CONNECTION) {
					bindType = BIND_CONNECTION;
				} else if (bind->getNodeType() == types::nodeType::DISCONNECTION) {
					bindType = BIND_DISCONNECTION;
				} else if (bind->getNodeType() == types::nodeType::DELEGATION) {
					bindType = BIND_DELEGATION;
				} else {
					throw exceptions::runtime::CWrongBindTypeException(bindType);
				}
				connection->getPortByName("bindType")->connectPort(bootstrapStringValue(bindType)->getDefaultPort());

				servicesNames["setSourceType"] = prepareStringSetter("sourceType");
				servicesNames["getSourceType"] = prepareStringGetter("sourceType");
				servicesNames["setSourceComponent"] = prepareStringSetter("sourceComponent");
				servicesNames["getSourceComponent"] = prepareStringGetter("sourceComponent");
				servicesNames["setSourcePort"] = prepareStringSetter("sourcePort");
				servicesNames["getSourcePort"] = prepareStringGetter("sourcePort");

				servicesNames["setDestinationType"] = prepareStringSetter("destinationType");
				servicesNames["getDestinationType"] = prepareStringGetter("destinationType");
				servicesNames["setDestinationComponent"] = prepareStringSetter("destinationComponent");
				servicesNames["getDestinationComponent"] = prepareStringGetter("destinationComponent");
				servicesNames["setDestinationPort"] = prepareStringSetter("destinationPort");
				servicesNames["getDestinationPort"] = prepareStringGetter("destinationPort");

				servicesNames["setBindType"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_string) stringComponent = cast(mem_string)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner());
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("bindType")->disconnectPortAt(0);
					context->getPortByName("bindType")->connectPort(stringComponent->getDefaultPort());
					return nullptr;
				};
				servicesNames["getBindType"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_port) port = context->getPortByName("bindType");
					port = port->getConnectedPortAt(0);
					port = port->getOwner()->getPortByName("default");

					return port;
				};
				servicesNames["setSourceComponentIndex"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("sourceComponentIndex")->connectPort(bootstrapIntValue(index)->getDefaultPort());
					return nullptr;
				};
				servicesNames["getSourceComponentIndex"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_int)(context->getPortByName("sourceComponentIndex")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames["setSourceComponentInvocation"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner()->getBottomChild();
					if (!invocation.use_count()) {
						invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					}
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("sourceComponentInvocation")->disconnectPortAt(0);
					context->getPortByName("sourceComponentInvocation")->connectPort(invocation->getPortByName("default"));
					return nullptr;
				};
				servicesNames["getSourceComponentInvocation"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};
				servicesNames["setDestinationComponentIndex"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 index = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("destinationComponentIndex")->connectPort(bootstrapIntValue(index)->getDefaultPort());
					return nullptr;
				};
				servicesNames["getDestinationComponentIndex"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return cast(mem_int)(context->getPortByName("destinationComponentIndex")->getConnectedPortAt(0)->getOwner())->getDefaultPort();
				};
				servicesNames["setDestinationComponentInvocation"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner()->getBottomChild();
					if (!invocation.use_count()) {
						invocation = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					}
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("destinationComponentInvocation")->disconnectPortAt(0);
					context->getPortByName("destinationComponentInvocation")->connectPort(invocation->getPortByName("default"));
					return nullptr;
				};
				servicesNames["getDestinationComponentInvocation"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					return context->getPortByName("destinationComponentInvocation")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
				};

				bootstrapEpilogue(connection, servicesNames);
				return connection;
			}

			ptr(mem_component) CBootstrapStage1::bootstrapInterfaceComponent(ptr(mem_component) owner) {
				std::map<std::string, std::function<ptr(mem_port)(const ptr(mem_component)&)> > servicesNames;
				ptr(mem_component) interface = bootstrapPrologueWithComponent(m_coreModules->getCoreDescriptor("Interface"), owner);

				servicesNames["setType"] = prepareStringSetter("type");
				servicesNames["getType"] = prepareStringGetter("type");

				servicesNames["getSignaturesCount"] = [this](const ptr(mem_component)& context) -> ptr(mem_port) {
					u64 count = context->getPortByName("signatures")->getConnectedPortsNumber();

					return bootstrapIntValue(count)->getDefaultPort();
				};
				servicesNames["getSignatureAt"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_SIGNATURES) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getSignatureAt");
					}
					u64 val = cast(mem_int)(context->getPortByName("args")->getConnectedPortAt(0)->getOwner())->getValue();
					context->getPortByName("args")->disconnectPortAt(0);
					return context->getPortByName("signatures")->getConnectedPortAt(val)->getOwner()->getPortByName("default");
				};
				servicesNames["addSignature"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_SIGNATURES) {
						throw exceptions::runtime::CWrongPortTypeException(type, "addSignature");
					}
					ptr(mem_component) signature = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();
					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("signatures")->connectPort(signature->getPortByName("default"));
					return nullptr;
				};
				servicesNames["getConnectedComponentName"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getConnectedComponentName");
					}
					if (context->getPortByName("componentName")->getConnectedPortsNumber()) {
						return context->getPortByName("componentName")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames["setConnectedComponentName"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
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
				servicesNames["getConnectedComponent"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "getConnectedComponent");
					}
					if (context->getPortByName("component")->getConnectedPortsNumber()) {
						return context->getPortByName("component")->getConnectedPortAt(0)->getOwner()->getPortByName("default");
					}
					return nullptr;
				};
				servicesNames["setConnectedComponent"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
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
				servicesNames["getServiceAt"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
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
				servicesNames["addService"] = [](const ptr(mem_component)& context) -> ptr(mem_port) {
					std::string type = cast(mem_string)(context->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue();
					if (type != PORT_TYPE_NAMED) {
						throw exceptions::runtime::CWrongPortTypeException(type, "addService");
					}
					ptr(mem_component) service = context->getPortByName("args")->getConnectedPortAt(0)->getOwner();

					context->getPortByName("args")->disconnectPortAt(0);
					context->getPortByName("services")->connectPort(service->getPortByName("default"));
					return nullptr;
				};

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