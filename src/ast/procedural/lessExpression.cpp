#include "ast/procedural/lessExpression.h"

namespace ast {

	namespace procedural {

		CLessExpression::CLessExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		                                  std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LESS_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LESS, op1, op2) {
		}
	}

}