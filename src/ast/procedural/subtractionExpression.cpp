#include "ast/procedural/subtractionExpression.h"

namespace ast {

	namespace procedural {

		CSubtractionExpression::CSubtractionExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::SUBTRACTION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::MINUS, op1, op2) {
		}
	}

}