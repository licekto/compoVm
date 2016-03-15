#include "ast/procedural/greaterExpression.h"

namespace ast {

	namespace procedural {

		CGreaterExpression::CGreaterExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		                                        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::GREATER_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::GREATER, op1, op2) {
		}

		void CGreaterExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}