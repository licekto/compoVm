#include "ast/nodes/compo/dereferenceLiteral.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		CDereferenceLiteral::CDereferenceLiteral(std::shared_ptr<ast::nodes::procedural::CSymbol> parameter)
			:   CNode(types::nodeType::DEREFERENCE),
			    m_parameter(parameter) {
		}

		void CDereferenceLiteral::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CDereferenceLiteral::getParamName() const {
			return m_parameter;
		}
	}
    }
}