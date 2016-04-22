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
                
                if (m_ports.find(var) != m_ports.end()) {
                    m_ports[var].m_connectingPort = port;
                }
            }

            void CContext::connectPorts() {
                for (auto item : m_ports) {
                    if (item.second.m_origPort.use_count() && item.second.m_connectingPort.use_count()) {
                        item.second.m_origPort->connectPort(item.second.m_connectingPort);
                    }
                }
            }

            void CContext::setPort(const std::string& var, ptr(mem_port) port) {
                setVariable(var, port);
                m_ports[var].m_origPort = port;
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
                return getVariable(var, 0);
            }
            
            ptr(mem_port) CContext::getVariable(const std::string& var, i64 index) {
                if (m_contextComponent.use_count()) {
                    try {
                        ptr(mem_port) port = m_contextComponent->getPortByName(var);
                        if (var == "self") {
                            return m_contextComponent->getPortByName("default");
                        }
                        if (port->getConnectedPortsNumber()) {
                            return port->getConnectedPortAt(index);
                        }
                    }
                    catch (const exceptions::runtime::CPortNotFoundException& ex) {
                    }
                }
                ptr(CVariablesTable) table = getTableWithVariable(var);
                if (table->variableFound(var)) {
                    return table->getVariable(var);
                }
                throw exceptions::runtime::CVariableNotFoundException(var);
            }

            void CContext::setContextComponent(ptr(mem_component) component) {
                m_contextComponent = component;
            }

            ptr(mem_component) CContext::getContextComponent() {
                return m_contextComponent;
            }

            void CContext::setServiceName(const std::string& name) {
                m_serviceName = name;
            }

            std::string CContext::getServiceName() const {
                return m_serviceName;
            }

            void CContext::clear() {
                m_stack.clear();
            }

	}
        
}