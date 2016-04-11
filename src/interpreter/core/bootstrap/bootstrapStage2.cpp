#include "interpreter/core/bootstrap/bootstrapStage2.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			CBootstrapStage2::CBootstrapStage2() {

			}

			ptr(mem_component) CBootstrapStage2::bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor) {
//			ptr(mem_component) parentComponent = new_ptr(mem_component)();
//                        ptr(mem_component) component = new_ptr(mem_component)();
//                        ptr(ast_descriptor) coreComponent = m_coreModules->getCoreDescriptor("Component");
//			ptr(ast_descriptor) coreDescriptor = m_coreModules->getCoreDescriptor("Descriptor");
//
//                        ptr(ast_port) port = coreComponent->getPortByName("default");
//                        ptr(mem_port) generalPort = new_ptr(mem_port)(bootstrapPortComponent(port, nullptr), port->getVisibility(), port->getRole());
//                        generalPort->getPort()->getPortByName("owner")->setOwner(component);
//                        parentComponent->addPort(generalPort);
//
//                        addPorts(parentComponent, coreComponent);
//                        addServices(parentComponent, coreComponent);
//
//                        component->setParent(parentComponent);
//                        parentComponent->setChild(component);
//
//                        addPorts(component, coreDescriptor);
//                        addServices(component, coreDescriptor);
//
//                        component->getPortByName("name")->connectPort(bootstrapStringValue(descriptor->getNameSymbol()->getStringValue())->getDefaultPort());
//
//                        for (size_t i = 0; i < descriptor->getPortsSize(); ++i) {
//                            component->getPortByName("ports")->connectPort(bootstrapPortDescriptionComponent(descriptor->getPortAt(i), component)->getPortByName("default"));
//                        }
//
//                        if (descriptor->getArchitecture().use_count()) {
//                            for (size_t i = 0; i < descriptor->getArchitecture()->getBodySize(); ++i) {
//                                ptr(ast_bind) bind = descriptor->getArchitecture()->getBodyNodeAt(i);
//                                component->getPortByName("architectureDefinition")->connectPort(bootstrapConnectionDescriptionComponent(bind, component)->getPortByName("default"));
//                            }
//                        }
//
//                        for (size_t i = 0; i < descriptor->getServicesSize(); ++i) {
//                            ptr(ast_service) service = descriptor->getServiceAt(i);
//                            component->getPortByName("services")->connectPort(bootstrapServiceComponent(service, component)->getPortByName("default"));
//                        }
//
//                        component->removeServiceByName("new");
//
//                        std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> callback;
//                        callback = [this](const std::vector<ptr(mem_component)>& /*params*/, const ptr(mem_component)& context) -> ptr(mem_port) {
//                                ptr(mem_component) componentNew = new_ptr(mem_component)();
//
//                                // TODO set proper owner
//                                //                                                   ||
//                                //                                                  \||/
//                                //                                                   \/
//                                ptr(mem_component) parent = bootstrapRootComponent(nullptr);
//                                componentNew->setParent(parent);
//                                parent->setChild(componentNew);
//
//                                componentNew->getPortByName("descriptorPort")->connectPort(context->getPortByName("default"));
//
//
//                                for (size_t i = 0; i < componentNew->getPortByName("ports")->getConnectedPortsNumber(); ++i) {
//                                    ptr(mem_component) portDescriptionComponent = componentNew->getPortByName("ports")->getConnectedPortAt(i)->getOwner();
//
//                                }
//			};
//
//                        generalPort = component->getPortByName("default")->getPort()
//                                                        ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
//                                                        ->getPortByName("services");
//                        component->connectAllServicesTo(generalPort);
//
//                        generalPort = component->getPortByName("self")->getPort()
//                                ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
//                                ->getPortByName("services");
//                        component->connectAllServicesTo(generalPort);
//
//                        generalPort = component->getPortByName("super")->getPort()
//                                ->getPortByName("interfaceDescription")->getConnectedPortAt(0)->getOwner()
//                                ->getPortByName("services");
//                        component->connectAllParentServicesTo(generalPort);
//
//			return component;
			}

		}

	}
}