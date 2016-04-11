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
                                //ptr(mem_component) interface = new_ptr(mem_component)(description->getPortByName("interfaceDefinition")->getConnectedPortAt(0)->getOwner());
				//port->getPortByName("interfaceDescription")->connectPort();
                        }

                        ptr(mem_component) CBootstrapStage2::cloneInterface(ptr(mem_component) interface) {
                                ptr(mem_component) newInterface = m_bootstrapStage1->bootstrapInterfaceComponent(nullptr);
                                
                        }

			ptr(mem_component) CBootstrapStage2::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
				ptr(mem_component) parentComponent = new_ptr(mem_component)();
				ptr(mem_component) component = new_ptr(mem_component)();
				ptr(ast_descriptor) coreComponent = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Component");
				ptr(ast_descriptor) coreDescriptor = m_bootstrapStage1->m_coreModules->getCoreDescriptor("Descriptor");

				ptr(ast_port) port = coreComponent->getPortByName("default");
				ptr(mem_port) generalPort = new_ptr(mem_port)(m_bootstrapStage1->bootstrapPortComponent(port, nullptr), port->getVisibility(), port->getRole());
				generalPort->getPort()->getPortByName("owner")->setOwner(component);
				parentComponent->addPort(generalPort);

				addPorts(parentComponent, coreComponent);
				addServices(parentComponent, coreComponent);

				component->setParent(parentComponent);
				parentComponent->setChild(component);

				addPorts(component, coreDescriptor);
				addServices(component, coreDescriptor);

				component->getPortByName("name")->connectPort(m_bootstrapStage1->bootstrapStringValue(descriptor->getNameSymbol()->getStringValue())->getDefaultPort());

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
					ptr(mem_component) componentNew = new_ptr(mem_component)();

					// TODO set proper owner
					//                                                   ||
					//                                                  \||/
					//                                                   \/
					ptr(mem_component) parent = bootstrapRootComponent(nullptr);
					componentNew->setParent(parent);
					parent->setChild(componentNew);

					componentNew->getPortByName("descriptorPort")->connectPort(context->getPortByName("default"));


					for (size_t i = 0; i < componentNew->getPortByName("ports")->getConnectedPortsNumber(); ++i) {
						ptr(mem_component) portDescriptionComponent = componentNew->getPortByName("ports")->getConnectedPortAt(i)->getOwner();
                                                
					}
				};

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