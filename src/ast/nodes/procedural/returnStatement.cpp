#include "ast/nodes/procedural/returnStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CReturnStatement::CReturnStatement(std::shared_ptr<ast::nodes::procedural::CAbstractExpression> expression)
			:   CNode(types::nodeType::RETURN),
			    m_expression(expression) {
		}

		void CReturnStatement::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CReturnStatement::getExpression() const {
			return m_expression;
		}

	}
    }
}