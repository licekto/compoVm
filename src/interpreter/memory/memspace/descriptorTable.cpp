#include "interpreter/memory/memspace/descriptorTable.h"
#include "exceptions/semantic/undefinedDescriptorException.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			void CDescriptorTable::addDescriptor(ptr(mem_component) descriptor) {
				m_table.push_back(descriptor);
			}

			ptr(mem_component) CDescriptorTable::getDescriptor(const std::string& name) {
				auto it = std::find_if(m_table.begin(), m_table.end(), [&name](ptr(mem_component) descriptor) {
					std::string tmpName = cast(mem_string)(descriptor->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue();
					return tmpName == name;
				});

				if (it == m_table.end()) {
					return nullptr;
				}
				return *it;
			}

			bool CDescriptorTable::descriptorFound(const std::string& name) {
				return getDescriptor(name).use_count() != 0;
			}

			void CDescriptorTable::clear() {
				m_table.clear();
			}

		}

	}
}