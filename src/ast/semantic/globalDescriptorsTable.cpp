#include "ast/semantic/globalDescriptorsTable.h"

namespace ast {

	namespace semantic {

		bool CGlobalDescriptorTable::symbolFound(std::string name) const {
			return m_descriptorMap.find(name) != m_descriptorMap.end();
		}

		void CGlobalDescriptorTable::addSymbol(ptr(ast_descriptorinterface) node) {
			m_descriptorMap[node->getNameSymbol()->getStringValue()] = node;
		}

		ptr(ast_descriptorinterface) CGlobalDescriptorTable::getSymbol(std::string name) {
			if (!symbolFound(name)) {
				return nullptr;
			}
			return m_descriptorMap[name];
		}


	}
}