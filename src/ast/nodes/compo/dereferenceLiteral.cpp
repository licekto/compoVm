#include "ast/nodes/compo/dereferenceLiteral.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		CDereferenceLiteral::CDereferenceLiteral(std::shared_ptr<ast::nodes::procedural::CSymbol> parameter)
			:   CNode(types::nodeType::DEREFERENCE),
			    m_parameter(parameter) {
		}

		void CDereferenceLiteral::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CDereferenceLiteral::getParamName() const {
			return m_parameter;
		}
	}
    }
}