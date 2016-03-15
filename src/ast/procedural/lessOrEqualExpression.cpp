#include "ast/procedural/lessOrEqualExpression.h"

namespace ast {

	namespace procedural {

		CLessOrEqualExpression::CLessOrEqualExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LESS_OR_EQUAL_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LESS_OR_EQUAL, op1, op2) {
		}

		void CLessOrEqualExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}