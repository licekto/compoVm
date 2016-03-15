#include "ast/procedural/greaterOrEqualExpression.h"

namespace ast {

	namespace procedural {

		CGreaterOrEqualExpression::CGreaterOrEqualExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::GREATER_OR_EQUAL_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::GREATER_OR_EQUAL, op1, op2) {
		}

		void CGreaterOrEqualExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}