#include "ast/compo/dereferenceLiteral.h"

namespace ast {

	namespace compo {

		CDereferenceLiteral::CDereferenceLiteral(std::shared_ptr<ast::procedural::CSymbol> parameter)
			:   CNode(types::nodeType::DEREFERENCE),
			    m_parameter(parameter) {
		}

		void CDereferenceLiteral::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::procedural::CSymbol> CDereferenceLiteral::getParamName() const {
			return m_parameter;
		}
	}

}