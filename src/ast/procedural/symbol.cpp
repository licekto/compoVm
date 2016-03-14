#include "ast/procedural/symbol.h"

namespace ast {

	namespace procedural {

		CSymbol::CSymbol(const std::string& name)
			: CNode(types::nodeType::SYMBOL),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(name) {
		}

		void CSymbol::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::string CSymbol::getStringValue() const {
			return m_name;
		}

	}

}