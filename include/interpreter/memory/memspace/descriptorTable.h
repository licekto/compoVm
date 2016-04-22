#pragma once

#include <map>

#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			class CDescriptorTable {
			  private:
				std::map<std::string, ptr(mem_component)> m_table;

			  public:
				void addDescriptor(ptr(mem_component) descriptor);

				void addNamedDescriptor(ptr(mem_component) descriptor, const std::string& name);

				ptr(mem_component) getDescriptor(const std::string& name);

				bool descriptorFound(const std::string& name) const;

				void clear();
			};

		}

	}
}
