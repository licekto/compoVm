#include "interpreter/memory/manager/manager.h"

namespace interpreter {

	namespace memory {

		namespace manager {
                    
                    CMemoryManager::CMemoryManager(std::shared_ptr<core::CCoreModules> coreModules)
                    : m_coreModules(coreModules) {
                    }
                    
                    void CMemoryManager::iterateAddPorts(std::shared_ptr<ast_reqprov> reqprov, std::function<void(objects::visibility, objects::type, ptr(ast_port))> callback) {
                        for (size_t i = 0; i < reqprov->getNumberOfPorts(); ++i) {
                                objects::visibility v = reqprov->getVisibilityType() == ast::nodes::types::visibilityType::EXTERNAL
                                        ? objects::visibility::EXTERNAL : objects::visibility::INTERNAL;

                                objects::type t = reqprov->getNodeType() == ast::nodes::types::REQUIREMENT
                                        ? objects::type::REQUIREMENT : objects::type::PROVISION;

                                callback(v, t, reqprov->getPortAt(i));
                            }
                    }
                    
                    void CMemoryManager::addPrimitivePorts(ptr(objects::CComponent) component, ptr(ast_descriptor) descriptor) {                        
                        // lambda function
                        auto callback = [this, &component](objects::visibility v, objects::type t, ptr(ast_port) port) {
                                if (port->isCollection()) {
                                    component->addPort(new_ptr(objects::TPortProperties)(v, t, nullptr, new_ptr(objects::CPrimitiveCollectionPort)(port->getNameSymbol()->getStringValue(), component)));
                                }
                                else {
                                    component->addPort(new_ptr(objects::TPortProperties)(v, t, nullptr, new_ptr(objects::CPrimitivePort)(port->getNameSymbol()->getStringValue(), component)));
                                }
                        };
                        
                        iterateAddPorts(descriptor->getInRequirement(), callback);
                        iterateAddPorts(descriptor->getExRequirement(), callback);
                        iterateAddPorts(descriptor->getInProvision(), callback);
                        iterateAddPorts(descriptor->getExProvision(), callback);
                    }
                    
                    ptr(objects::CComponent) CMemoryManager::bootstrapPortComponent(ptr(ast_port) astPort, ptr(objects::CComponent) owner) {
                        ptr(objects::CComponent) port = new_ptr(objects::CComponent)();
                        ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Port");
                        
                        addPrimitivePorts(port, descriptor);
                        
                        std::string name = astPort->getNameSymbol()->getStringValue();
                        
                        port->getPrimitivePortByName(name)->setConnectedComponent(new_ptr(objects::CStringComponent)(name));
                        
                        port->getPrimitivePortByName("owner")->setConnectedComponent(owner);
                        
                        return nullptr;
                    }

                    void CMemoryManager::addPorts(ptr(objects::CComponent) component, ptr(ast_descriptor) descriptor) {
                        // lambda function
                        auto callback = [this, &component](objects::visibility v, objects::type t, ptr(ast_port) port) {
                            component->addPort(new_ptr(objects::TPortProperties)(v, t, bootstrapPortComponent(port, component)));
                        };
                        
                        iterateAddPorts(descriptor->getInRequirement(), callback);
                        iterateAddPorts(descriptor->getExRequirement(), callback);
                        iterateAddPorts(descriptor->getInProvision(), callback);
                        iterateAddPorts(descriptor->getExProvision(), callback);
                    }

                    ptr(objects::CComponent) CMemoryManager::bootstrapServiceComponent(ptr(ast_service) astService) {
                        
                    }
                    
                    ptr(objects::CComponent) CMemoryManager::bootstrapDescriptorComponent() {
                        ptr(objects::CComponent) component = new_ptr(objects::CComponent)();
                        ptr(ast_descriptor) descriptor = m_coreModules->getCoreDescriptor("Descriptor");
                        
                        addPorts(component, descriptor);
                        
                        return nullptr;
                        
                    }

                    void CMemoryManager::boostrap() {
                        if (m_coreModules.use_count()) {
                            for (size_t i = 0; i < m_coreModules->getCoreDescriptorsSize(); ++i) {
                                m_coreModules->getCoreDescriptorAt(i);
                            }
                                    
                        }
                        
                    }
                        
		}
	}
}