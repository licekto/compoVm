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
                                        std::string name = port->getNameSymbol()->getStringValue();
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

				for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
					ptr(ast_port) astPort = descriptor->getPortAt(i);
					ptr(mem_port) port = new_ptr(mem_port)(m_bootstrapStage1->bootstrapPortComponent(astPort, component), astPort->getVisibility(), astPort->getRole());
					component->addPort(port);
				}

				for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
					ptr(ast_service) astService = descriptor->getServiceAt(i);
					ptr(mem_service) service = new_ptr(mem_service)(m_bootstrapStage1->bootstrapServiceComponent(astService, component));
					component->addService(service);
				}

				component->connectAllServicesTo(component->getPortByName("default"));
				component->connectAllServicesTo(component->getPortByName("self"));
				component->getPortByName("owner")->connectPort(owner->getPortByName("default"));

				return component;
			}

			ptr(mem_component) CBootstrapStage2::buildPortFromDescription(ptr(mem_component) description, ptr(mem_component) owner) {

				ptr(mem_component) port = m_bootstrapStage1->bootstrapPortComponent(owner);

				std::string name = cast(mem_string)(description->getPortByName("name")->getOwner())->getValue();

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
				if (type == PORT_TYPE_INJECTED) {
					throw exceptions::semantic::CUnsupportedFeatureException("Injection port");
				}
				if (type == PORT_TYPE_NAMED) {
                                        std::string componentName = cast(mem_string)(interface->getPortByName("componentName")->getConnectedPortAt(0)->getOwner())->getValue();
                                        newInterface->getPortByName("componentName")->connectPort(m_bootstrapStage1->bootstrapStringValue(componentName)->getDefaultPort());
				}
				if (type == PORT_TYPE_UNIVERSAL) {
                                        if (portOwner.use_count()) {
                                            portOwner->connectAllServicesTo(newInterface->getPortByName("services"));
                                        }
				}
				else {
					throw exceptions::runtime::CUnknownPortTypeException();
				}
                                
				return nullptr;
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

			ptr(mem_component) CBootstrapStage2::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
				ptr(mem_component) parentComponent = new_ptr(mem_component)();
				ptr(mem_component) component = new_ptr(mem_component)();
				ptr(ast_descriptor) coreComponent = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Component");
				ptr(ast_descriptor) coreDescriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Descriptor");

				ptr(ast_port) port = coreComponent->getPortByName("default");
				ptr(mem_port) generalPort = new_ptr(mem_port)(m_bootstrapStage1->bootstrapPortComponent(port, nullptr), port->getVisibility(), port->getRole());
				parentComponent->addPort(generalPort);

				addPorts(parentComponent, coreComponent);
				addServices(parentComponent, coreComponent);
                                
                                parentComponent->getPortByName("default")->getPort()->getPortByName("owner")->connectPort(parentComponent->getPortByName("default"));
                                
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

				std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;
				callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
					ptr(mem_component) newComponent = new_ptr(mem_component)();

					// TODO set proper owner
					//                                                   ||
					//                                                  \||/
					//                                                   \/
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

					return newComponent->getPortByName("default");
				};
                                ptr(mem_service) newService = new_ptr(mem_service)(new_ptr(memory::objects::primitives::CPrimitiveService)("new", component, callback));
                                //component->addService(newService);

				generalPort = component->getPortByName("default")->getPort()
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