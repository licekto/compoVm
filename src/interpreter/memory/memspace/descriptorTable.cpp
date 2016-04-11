#include "interpreter/memory/memspace/descriptorTable.h"
#include "exceptions/semantic/undefinedDescriptorException.h"

namespace interpreter {

	namespace memory {

		namespace memspace {

			void CDescriptorTable::addDescriptor(ptr(mem_component) descriptor) {
				ptr(mem_port) port = descriptor->getPortByName("name");
				m_table[cast(mem_string)(port->getConnectedPortAt(0)->getOwner())->getValue()] = descriptor;
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