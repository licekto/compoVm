#pragma once

#include <memory>
#include <map>
#include <string>


namespace ast {
    /**
     *  \addtogroup core
     *  @{
     */

    /**
     * core Namespace to uniquely identify compo AST nodes.
     */    
    namespace core {
    
        class CGLobalDescriptorTable {
        private:
            std::map<std::string, std::weak_ptr<ast::compo::CAbstractDescriptorInterface> m_descriptorMap;
        };
    
    }
}
/*! @}*/