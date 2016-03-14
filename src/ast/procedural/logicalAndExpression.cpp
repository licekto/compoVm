#include "ast/procedural/logicalAndExpression.h"

namespace ast {

	namespace procedural {

		CLogicalAndExpression::CLogicalAndExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LOGICAL_AND_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LOGICAL_AND, op1, op2) {
		}
	}

}