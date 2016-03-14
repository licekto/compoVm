#include "ast/procedural/multiplicationExpression.h"

namespace ast {

	namespace procedural {

		CMultiplicationExpression::CMultiplicationExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::MULTIPLICATION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::TIMES, op1, op2) {
		}
	}

}