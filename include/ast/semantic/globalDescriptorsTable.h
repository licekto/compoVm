#pragma once

#include <memory>
#include <map>
#include <string>

#include "exceptions/semantic/redefinitionDescriptorException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedSymbolException.h"

#include "definitions.h"

namespace ast {
    /**
     *  \addtogroup core
     *  @{
     */

    /**
     * core Namespace to uniquely identify compo AST nodes.
     */    
    namespace semantic {
    
        /**
	 * \class CGLobalDescriptorTable
	 * \brief Abstract base class for other nodes.
	 */
        class CGlobalDescriptorTable {
        private:
            std::map<std::string, ptr(ast_descriptorinterface)> m_descriptorMap;
            
            bool findSymbol(std::string name) const;
            
        public:
            
            void addSymbol(ptr(ast_descriptorinterface) node);
            
            ptr(ast_descriptorinterface) getSymbol(std::string name);
        };
    
    }
}
/*! @}*/