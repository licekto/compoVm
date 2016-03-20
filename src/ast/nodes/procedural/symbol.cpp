#include "ast/nodes/procedural/symbol.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CSymbol::CSymbol(const std::string& name)
			: CNode(types::nodeType::SYMBOL),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_name(name) {
		}

		void CSymbol::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}

		std::string CSymbol::getStringValue() const {
			return m_name;
		}

	}
    }
}