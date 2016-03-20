#include "ast/nodes/procedural/stringLiteral.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CStringLiteral::CStringLiteral(const std::string& val)
			: CNode(types::nodeType::STRING_LITERAL),
			  m_stringValue(val) {
		}

		void CStringLiteral::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}

		std::string CStringLiteral::getValue() const {
			return m_stringValue;
		}
	}
    }
}