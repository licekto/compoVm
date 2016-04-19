#pragma once

#include <map>

#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			class CMemory {
			  private:
				std::vector<ptr(mem_component)> m_componentsMemory;
                                
                                std::vector<ptr(mem_port)> m_portsMemory;
                                
                                std::vector<ptr(mem_service)> m_servicesMemory;

			  public:
                                wptr(mem_component) newComponent();
                                
                                wptr(mem_int) newIntComponent(i64 value);
                                
                                wptr(mem_string) newStringComponent(const std::string& value);
                                
                                wptr(mem_bool) newBoolComponent(bool value);

                                wptr(mem_port) newPort();
                                
                                wptr(mem_service) newService();
                                
                                size_t getComponentsNumber() const;
                                
				wptr(mem_component) getComponentAt(size_t index);
			};

		}

	}
}
