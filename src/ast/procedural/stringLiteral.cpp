#include "ast/procedural/stringLiteral.h"

namespace ast {

	namespace procedural {

		CStringLiteral::CStringLiteral(const std::string& val)
			: CNode(types::nodeType::STRING_LITERAL),
			  m_stringValue(val) {
		}

		void CStringLiteral::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::string CStringLiteral::getValue() const {
			return m_stringValue;
		}
	}

}