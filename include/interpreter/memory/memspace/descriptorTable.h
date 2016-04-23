#pragma once

#include <vector>
#include <algorithm>

#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			class CDescriptorTable {
			  private:
				std::vector<ptr(mem_component)> m_table;

			  public:
				void addDescriptor(ptr(mem_component) descriptor);

				ptr(mem_component) getDescriptor(const std::string& name);

				bool descriptorFound(const std::string& name);

				void clear();
			};

		}

	}
}
