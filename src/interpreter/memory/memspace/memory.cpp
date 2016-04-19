#include "interpreter/memory/memspace/memory.h"
#include "interpreter/core/bootstrap/bootstrapStage1.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

                    CMemory::CMemory(ptr(core::bootstrap::CBootstrapStage1) bootstrap1) : m_bootstrap1(bootstrap1) {
                    }

                    void CMemory::setBootstrap1(ptr(core::bootstrap::CBootstrapStage1) bootstrap1) {
                        m_bootstrap1 = bootstrap1;
                    }

                    wptr(mem_component) CMemory::newComponent() {
                        ptr(mem_component) component = new_ptr(mem_component)();
                        m_componentsMemory.push_back(component);
                        
                        return wptr(mem_component)(component);
                    }

                    wptr(mem_int) CMemory::newIntComponent(i64 value) {
                        ptr(mem_int) component = new_ptr(mem_int)(value);
                        m_componentsMemory.push_back(component);
                        
                        return wptr(mem_int)(component);
                    }

                    wptr(mem_string) CMemory::newStringComponent(const std::string& value) {
                        ptr(mem_string) component = new_ptr(mem_string)(value);
                        m_componentsMemory.push_back(component);
                        
                        return wptr(mem_string)(component);
                    }

                    wptr(mem_bool) CMemory::newBoolComponent(bool value) {
                        ptr(mem_bool) component = new_ptr(mem_bool)(value);
                        m_componentsMemory.push_back(component);
                        
                        return wptr(mem_bool)(component);
                    }

                    wptr(mem_port) CMemory::newPrimitivePort(ptr(mem_component) owner, ptr(ast_port) port) {
                        return newPrimitivePort(owner,
                                                port->getNameSymbol()->getStringValue(),
                                                port->isCollection(),
                                                port->getVisibility(),
                                                port->getRole());
                    }

                    wptr(mem_port) CMemory::newPrimitivePort(ptr(mem_component) owner, const std::string& name, bool isCollection, type_visibility visibility, type_role role) {
                        ptr(mem_primitiveport) primitivePort = new_ptr(mem_primitiveport)(name, owner, isCollection);
                        m_primitivePortsMemory.push_back(primitivePort);
                        ptr(mem_port) newPort = new_ptr(mem_port)(primitivePort, visibility, role);
                        m_portsMemory.push_back(newPort);
                        
                        return wptr(mem_port)(newPort);
                    }

                    wptr(mem_port) CMemory::newComponentPort(ptr(mem_component) owner, ptr(ast_port) port) {
                        ptr(mem_port) newPort = new_ptr(mem_port)(m_bootstrap1->bootstrapPortComponent(port, owner), port->getVisibility(), port->getRole());
                        m_portsMemory.push_back(newPort);
                        
                        return wptr(mem_port)(newPort);
                    }
                    
                    wptr(mem_port) CMemory::newComponentPort(ptr(mem_component) port, type_visibility visibility, type_role role) {
                        ptr(mem_port) newPort = new_ptr(mem_port)(port, visibility, role);
                        m_portsMemory.push_back(newPort);
                        
                        return wptr(mem_port)(newPort);
                    }
                    
                    wptr(mem_service) CMemory::newPrimitiveService(ptr(mem_component) owner, const std::string& name, std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback) {
                        ptr(mem_primitiveservice) primitiveService = new_ptr(mem_primitiveservice)(name, owner, callback);
                        m_primitiveServicesMemory.push_back(primitiveService);
                        ptr(mem_service) service = new_ptr(mem_service)(primitiveService);
                        m_servicesMemory.push_back(service);
                        
                        return wptr(mem_service)(service);
                    }

                    wptr(mem_service) CMemory::newComponentService(ptr(mem_component) owner, ptr(ast_service) astService) {
                        ptr(mem_service) service = new_ptr(mem_service)(m_bootstrap1->bootstrapServiceComponent(astService, owner));
                        m_servicesMemory.push_back(service);
                        
                        return wptr(mem_service)(service);
                    }

                    wptr(mem_service) CMemory::newComponentService(ptr(mem_component) service) {
                        ptr(mem_service) newService = new_ptr(mem_service)(service);
                        m_servicesMemory.push_back(newService);
                        
                        return wptr(mem_service)(newService);
                    }

                    size_t CMemory::getComponentsNumber() const {
                        return m_componentsMemory.size();
                    }

		}

	}
}