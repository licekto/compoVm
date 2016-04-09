#include "ast/semantic/syntaxDescriptorsTable.h"

namespace ast {

	namespace semantic {

		bool CSyntaxDescriptorTable::symbolFound(std::string name) const {
			return m_descriptorMap.find(name) != m_descriptorMap.end();
		}

		void CSyntaxDescriptorTable::addSymbol(ptr(ast_descriptorinterface) node) {
			m_descriptorMap[node->getNameSymbol()->getStringValue()] = node;
		}

		ptr(ast_descriptorinterface) CSyntaxDescriptorTable::getSymbol(std::string name) {
			if (!symbolFound(name)) {
				return nullptr;
			}
			return m_descriptorMap[name];
		}

		void CSyntaxDescriptorTable::clear() {
			m_descriptorMap.clear();
		}
	}
}