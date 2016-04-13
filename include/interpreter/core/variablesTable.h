#pragma once

#include <map>

#include "types.h"
#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {
    
	namespace core {
            
		class CVariablesTable {
                private:
                    std::map<std::string,ptr(mem_port)> m_table;
                
                public:
                    bool variableFound(const std::string& var) const;
                    
                    void addVariable(const std::string& var);
                    
                    void setVariable(const std::string& var, ptr(mem_port) port);
                    
                    ptr(mem_port) getVariable(const std::string& var);
		};

	}
        
}