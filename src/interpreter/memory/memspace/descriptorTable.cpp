#include "interpreter/memory/memspace/descriptorTable.h"
#include "exceptions/semantic/undefinedDescriptorException.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			void CDescriptorTable::addDescriptor(ptr(mem_component) descriptor) {
                                addNamedDescriptor(descriptor, cast(mem_string)(descriptor->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue());
			}

                        void CDescriptorTable::addNamedDescriptor(ptr(mem_component) descriptor, const std::string& name) {
				m_table[name] = descriptor;
			}
                        
			ptr(mem_component) CDescriptorTable::getDescriptor(const std::string& name) {
				if (!descriptorFound(name)) {
					throw exceptions::semantic::CUndefinedDescriptorException(name);
				}
				return m_table.at(name);
			}

			bool CDescriptorTable::descriptorFound(const std::string& name) const {
				if (m_table.find(name) == m_table.end()) {
					return false;
				}
				return true;
			}

			void CDescriptorTable::clear() {
				m_table.clear();
			}

		}

	}
}