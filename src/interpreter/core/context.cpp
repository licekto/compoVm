#include "interpreter/core/context.h"
#include "exceptions/runtime/variableNotFoundException.h"

namespace interpreter {
    
	namespace core {

            void CContext::pushContext(ptr(ast_compound) node) {
                ptr(CVariablesTable) context = new_ptr(CVariablesTable)();
                for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
                    context->addVariable(node->getTemporaryAt(i)->getStringValue());
                }
                m_stack.push_back(context);
            }

            void CContext::pushContext() {
                m_stack.push_back(new_ptr(CVariablesTable)());
            }

            void CContext::popContext() {
                m_stack.pop_back();
            }

            ptr(CVariablesTable) CContext::getTopContext() {
                return m_stack.at(m_stack.size()-1);
            }

            void CContext::setVariable(const std::string& var, ptr(mem_port) port) {
                if (m_stack.empty()) {
                    pushContext();
                }
                getTableWithVariable(var)->setVariable(var, port);
            }

            void CContext::AddPort(ptr(mem_port) port) {
                m_ports[port->getName()] = port;
            }

            void CContext::addVariable(const std::string& var) {
                if (m_stack.empty()) {
                    pushContext();
                }
                getTopContext()->addVariable(var);
            }

            ptr(CVariablesTable) CContext::getTableWithVariable(const std::string& var) {
                for (ptr(CVariablesTable) table : m_stack) {
                    if (table->variableFound(var)) {
                        return table;
                    }
                }
                throw exceptions::runtime::CVariableNotFoundException(var);
            }

            ptr(mem_port) CContext::getVariable(const std::string& var) {
                ptr(CVariablesTable) table = getTableWithVariable(var);
                if (table->variableFound(var)) {
                    return table->getVariable(var);
                }
                throw exceptions::runtime::CVariableNotFoundException(var);
            }

            void CContext::clear() {
                m_stack.clear();
            }

	}
        
}