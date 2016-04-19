#pragma once

#include <map>

#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			class CMemory {
			  private:
				std::vector<ptr(mem_component)> m_memory;

			  public:
                                wptr(mem_component) getNewComponent();
                                
                                wptr(mem_int) getIntComponent(i64 value);
                                
                                wptr(mem_string) getStringComponent(const std::string& value);
                                
                                wptr(mem_bool) getBoolComponent(bool value);

                                size_t getComponentsNumber() const;
                                
				wptr(mem_component) getComponentAt(size_t index);
			};

		}

	}
}
