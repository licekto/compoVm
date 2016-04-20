#pragma once

#include <vector>

#include "types.h"
#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"
#include "interpreter/core/variablesTable.h"

namespace interpreter {
    
	namespace core {
            
		class CContext {
                private:
                    std::vector<ptr(CVariablesTable)> m_stack;
                    
                    std::map<std::string,ptr(mem_port)> m_ports;
                
                public:
                    void pushContext(ptr(ast_compound) node);
                    
                    void pushContext();
                    
                    void popContext();
                    
                    ptr(CVariablesTable) getTopContext();
                    
                    void setVariable(const std::string& var, ptr(mem_port) port);
                    
                    void AddPort(ptr(mem_port) port);
                    
                    void addVariable(const std::string& var);
                    
                    ptr(CVariablesTable) getTableWithVariable(const std::string& var);
                    
                    ptr(mem_port) getVariable(const std::string& var);
                    
                    void clear();
		};

	}
        
}