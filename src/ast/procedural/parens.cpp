#include "ast/procedural/parens.h"

namespace ast {

	namespace procedural {

		CParens::CParens(std::shared_ptr<ast::CNode> expr)
			: CNode(types::nodeType::PARENS),
			  CAbstractExpression(),
			  CAbstractPrimaryExpression(),
			  m_expression(expr) {
		}

		void CParens::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		std::shared_ptr<ast::CNode> CParens::getExpression() const {
			return m_expression;
		}
	}

}