#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/primitives/primitivePortProperties.h"
#include "interpreter/memory/objects/portProperties.h"
#include "interpreter/memory/objects/unsignedIntComponent.h"

namespace interpreter {

	namespace core {

		CBootstrap::CBootstrap(std::shared_ptr<core::CCoreModules> coreModules,
                                       const ptr(core::CInterpreter)& interpreter)
			: m_coreModules(coreModules),
                          m_interpreter(interpreter) {
                }

                ptr(memory::objects::CComponent) CBootstrap::bootstrapComponent() {
                    ptr(ast_descriptor) componentDescriptor = m_coreModules->getCoreDescriptor("Component");
                    
                    std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)> servicesNames;
                    
                    ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
                    
                    addPrimitivePorts(component, componentDescriptor);
                    addPrimitiveServices(component, componentDescriptor, servicesNames);
                    
                    std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> callback = 
                            [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent){
                        
                        ptr(memory::objects::CComponent) nameComponent = cast(memory::objects::primitives::CPrimitiveCollectionPort)
                                (cast(memory::objects::primitives::CPrimitivePortProperties)(context->getPortByName("args"))->getPrimitivePort())->getConnectedComponentAt(0);
                        
                        ptr(memory::objects::CStringComponent) name = cast(memory::objects::CStringComponent)(nameComponent);
                        
                        ptr(memory::objects::CAbstractPortProperties) properties = context->getPortByName(name->getValue());
                        
                        if (!context->getPortByName(name->getValue())->isPrimitive()) {
                            return cast(memory::objects::CPortProperties)(properties)->getPort();
                        }
                        return nullptr;
                    };
                    
                    servicesNames.at("getPortNamed")->setCallback(callback);
                    
                    callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent){
                        return nullptr;
                    };
                    
                    servicesNames.at("getPorts")->setCallback(callback);
                    servicesNames.at("getDescriptor")->setCallback(callback);
                    
                    callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& context) -> ptr(memory::objects::CComponent){
                        return context;
                    };
                    
                    servicesNames.at("getOwner")->setCallback(callback);
                    
                    callback = [](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& /*context*/) -> ptr(memory::objects::CComponent){
                        //return new_ptr(memory::objects::CUnsignedIntComponent)(std::hash<memory::objects::CComponent>()(context.get()));
                        return 0;
                    };
                    
                    servicesNames.at("getIdentityHash")->setCallback(callback);
                    
                    ptr(interpreter::memory::objects::primitives::CPrimitivePort) defaultPort = cast(interpreter::memory::objects::primitives::CPrimitivePort)
                            (cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("default"))->getPrimitivePort());
                    ptr(interpreter::memory::objects::primitives::CPrimitivePort) selfPort = cast(interpreter::memory::objects::primitives::CPrimitivePort)
                            (cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("self"))->getPrimitivePort());
                    
                    for(auto const &record : servicesNames) {
                        defaultPort->setConnectedService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
                        selfPort->setConnectedService(new_ptr(interpreter::memory::objects::CGeneralService)(record.second));
                    }
                    
                    return component;
                }

                void CBootstrap::addPrimitiveServices(std::shared_ptr<memory::objects::CComponent> component, std::shared_ptr<ast_descriptor> descriptor,
                                                      std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)>& servicesNames) {
                    
                    for(size_t i = 0; i < descriptor->getServicesSize(); ++i) {
                        ptr(ast_service) astService = descriptor->getServiceAt(i);
                        
                        std::string serviceName = astService->getNameSymbol()->getStringValue();
                        
                        ptr(memory::objects::primitives::CPrimitiveService) primitiveService =
                                new_ptr(memory::objects::primitives::CPrimitiveService)(serviceName, component);
                        
                        for (size_t j = 0; j < astService->getParamsSize(); ++j) {
                            primitiveService->setParam(cast(ast::nodes::procedural::CSymbol)(astService->getParamAt(j))->getStringValue());
                        }
                        
                        servicesNames[serviceName] = primitiveService;
                        component->addService(new_ptr(memory::objects::CGeneralService)(primitiveService));
                    }
                    
                }

		void CBootstrap::iterateAddPorts(std::shared_ptr<ast_reqprov> reqprov, std::function<void(memory::objects::portVisibility, memory::objects::portType, ptr(ast_port))> callback) {
                    if (reqprov.use_count()) {
			for (size_t i = 0; i < reqprov->getNumberOfPorts(); ++i) {
				memory::objects::portVisibility v = reqprov->getVisibilityType() == ast::nodes::types::visibilityType::EXTERNAL
				                                    ? memory::objects::portVisibility::EXTERNAL : memory::objects::portVisibility::INTERNAL;

				memory::objects::portType t = reqprov->getNodeType() == ast::nodes::types::REQUIREMENT
				                              ? memory::objects::portType::REQUIREMENT : memory::objects::portType::PROVISION;

				callback(v, t, reqprov->getPortAt(i));
			}
                    }
		}

		void CBootstrap::addPrimitivePorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor) {
			// lambda function
			auto callback = [this, &component](memory::objects::portVisibility v, memory::objects::portType t, ptr(ast_port) port) {
                                bool primitive = true;
				if (port->isCollection()) {
					component->addPort(new_ptr(memory::objects::primitives::CPrimitivePortProperties)
                                            (new_ptr(memory::objects::primitives::CPrimitiveCollectionPort)(port->getNameSymbol()->getStringValue(), component), v, t, primitive));
				} else {
                                        component->addPort(new_ptr(memory::objects::primitives::CPrimitivePortProperties)
                                            (new_ptr(memory::objects::primitives::CPrimitivePort)(port->getNameSymbol()->getStringValue(), component), v, t, primitive));
				}
			};

			iterateAddPorts(descriptor->getInRequirement(), callback);
			iterateAddPorts(descriptor->getExRequirement(), callback);
			iterateAddPorts(descriptor->getInProvision(), callback);
			iterateAddPorts(descriptor->getExProvision(), callback);
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner) {
			ptr(memory::objects::CComponent) port = new_ptr(memory::objects::CComponent)();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Port");

			addPrimitivePorts(port, descriptor);

			std::string name = astPort->getNameSymbol()->getStringValue();

			cast(memory::objects::primitives::CPrimitivePort)(port->getPortByName("name"))->setConnectedComponent(new_ptr(memory::objects::CStringComponent)(name));
			cast(memory::objects::primitives::CPrimitivePort)(port->getPortByName("owner"))->setConnectedComponent(owner);

			return port;
		}

		void CBootstrap::addPorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor) {
			// lambda function
			auto callback = [this, &component](memory::objects::portVisibility v, memory::objects::portType t, ptr(ast_port) port) {
                                bool primitive = false;
				component->addPort(new_ptr(memory::objects::CPortProperties)(bootstrapPortComponent(port, component), v, t, primitive));
			};

			iterateAddPorts(descriptor->getInRequirement(), callback);
			iterateAddPorts(descriptor->getExRequirement(), callback);
			iterateAddPorts(descriptor->getInProvision(), callback);
			iterateAddPorts(descriptor->getExProvision(), callback);
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context) {
			ptr(memory::objects::CComponent) service = new_ptr(memory::objects::CComponent)();

			addPrimitivePorts(service, m_coreModules->getCoreDescriptor("Service"));

			auto connectComponentFunc = [&service](const std::string& name, ptr(memory::objects::CComponent) component) {
				cast(memory::objects::primitives::CPrimitiveCollectionPort)
				(cast(memory::objects::CPortProperties)(service->getPortByName(name))->getPort()->getPortByName("connectedPorts"))->connectComponent(component);
			};

			connectComponentFunc("context", context);
			connectComponentFunc("serviceSign", bootstrapServiceSignatureComponent(astService->getSignature()));
			connectComponentFunc("code", new_ptr(memory::objects::CStringComponent)(astService->getBodyCode()));
                        
                        std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> executeCallback = 
                        // No parameters for primitive service "execute"
                            [this](const std::vector<ptr(memory::objects::CComponent)>& /*params*/, const ptr(memory::objects::CComponent)& currentContext) -> ptr(memory::objects::CComponent) {
                                if (currentContext.use_count()) {
                                    // Obtain code
                                    ptr(memory::objects::CComponent) component = cast(memory::objects::primitives::CPrimitiveCollectionPort)
                                        (cast(memory::objects::CPortProperties)(currentContext->getPortByName("code"))->getPort()->getPortByName("connectedPorts"))->getConnectedComponentAt(0);

                                    ptr(memory::objects::CStringComponent) code = cast(memory::objects::CStringComponent)(component);

                                    m_interpreter->execService(code->getValue());
                                }
                                return nullptr;
                            };
                        
			service->addService(new_ptr(memory::objects::CGeneralService)(new_ptr(memory::objects::primitives::CPrimitiveService)("execute", service, executeCallback)));

			return service;
		}

		std::shared_ptr<memory::objects::CComponent> CBootstrap::bootstrapServiceSignatureComponent(ptr(ast_servicesignature) /*astSignature*/) {
			ptr(memory::objects::CComponent) serviceSignature = new_ptr(memory::objects::CComponent)();

			addPorts(serviceSignature, m_coreModules->getCoreDescriptor("ServiceSignature"));

			return serviceSignature;
		}

		ptr(memory::objects::CComponent) CBootstrap::bootstrapDescriptorComponent() {
			ptr(memory::objects::CComponent) component = new_ptr(memory::objects::CComponent)();
			ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Descriptor");

			addPorts(component, descriptor);

			return component;
                }

		void CBootstrap::boostrap() {
			if (m_coreModules.use_count()) {
                            m_coreModules->loadCoreModules();
                            
                            //m_coreComponentsMap[core::coreModuleType::DESCRIPTOR] = bootstrapDescriptorComponent();
                            m_coreComponentsMap[core::coreModuleType::COMPONENT] = bootstrapComponent();
			}
                }

                ptr(memory::objects::CComponent) CBootstrap::getCoreComponent(core::coreModuleType type) {
                    return m_coreComponentsMap[type];
                }

	}
}