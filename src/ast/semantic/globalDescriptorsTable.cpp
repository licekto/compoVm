#include "ast/semantic/globalDescriptorsTable.h"

namespace ast {

    namespace semantic {
        
        bool CGlobalDescriptorTable::findSymbol(std::string name) const {
            return m_descriptorMap.find(name) == m_descriptorMap.end();
        }
        
        void CGlobalDescriptorTable::addSymbol(ptr(ast_descriptorinterface) node) {
            if (findSymbol(node->getNameSymbol()->getStringValue())) {
                throw exceptions::semantic::CRedefinitionDescriptorException(node->getNameSymbol()->getStringValue());
            }
            m_descriptorMap[node->getNameSymbol()->getStringValue()] = node;
        }
        
        ptr(ast_descriptorinterface) CGlobalDescriptorTable::getSymbol(std::string name) {
            if (!findSymbol(name)) {
                throw exceptions::semantic::CUndefinedSymbolException(name);
            }
            return m_descriptorMap[name];
        }

        
    }
}