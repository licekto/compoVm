#include "interpreter/memory/memspace/memory.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

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

                    wptr(mem_port) CMemory::newPort() {

                    }

                    wptr(mem_service) CMemory::newService() {

                    }

                    size_t CMemory::getComponentsNumber() const {
                        return m_componentsMemory.size();
                    }

                    wptr(mem_component) CMemory::getComponentAt(size_t index) {
                        return wptr(mem_component)(m_componentsMemory.at(index));
                    }

		}

	}
}