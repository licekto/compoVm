#include "interpreter/core/variablesTable.h"
#include "exceptions/runtime/variableRedefinitionException.h"
#include "exceptions/runtime/variableNotFoundException.h"

namespace interpreter {
    
	namespace core {

            bool CVariablesTable::variableFound(const std::string& var) const {
                auto it = m_table.find(var);
                if (it == m_table.end()) {
                    return false;
                }
                return true;
            }

            void CVariablesTable::addVariable(const std::string& var) {
                if (variableFound(var)) {
                    throw exceptions::runtime::CVariableRedefinitionException(var);
                }
                m_table[var] = nullptr;
            }

            void CVariablesTable::setVariable(const std::string& var, ptr(mem_port) port) {
                if (!variableFound(var)) {
                    throw exceptions::runtime::CVariableNotFoundException(var);
                }
                m_table[var] = port;
            }

            ptr(mem_port) CVariablesTable::getVariable(const std::string& var) {
                if (!variableFound(var)) {
                    throw exceptions::runtime::CVariableNotFoundException(var);
                }
                return m_table.at(var);
            }

	}
        
}