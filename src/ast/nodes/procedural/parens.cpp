#include "ast/nodes/procedural/parens.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CParens::CParens(std::shared_ptr<ast::nodes::CNode> expr)
				: CNode(types::nodeType::PARENS),
				  CAbstractExpression(),
				  CAbstractPrimaryExpression(),
				  m_expression(expr) {
			}

			void CParens::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::CNode> CParens::getExpression() const {
				return m_expression;
			}
		}
	}
}