#include "ast/procedural/returnStatement.h"

namespace ast {

	namespace procedural {

		CReturnStatement::CReturnStatement(std::shared_ptr<ast::procedural::CAbstractExpression> expression)
			:   CNode(types::nodeType::RETURN),
			    m_expression(expression) {
		}

		void CReturnStatement::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		std::shared_ptr<ast::procedural::CAbstractExpression> CReturnStatement::getExpression() const {
			return m_expression;
		}

	}

}