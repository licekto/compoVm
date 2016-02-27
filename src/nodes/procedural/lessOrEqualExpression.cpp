#include "nodes/procedural/lessOrEqualExpression.h"

namespace nodes {

	namespace procedural {

		CLessOrEqualExpression::CLessOrEqualExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LESS_OR_EQUAL_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LESS_OR_EQUAL, op1, op2) {
		}
	}

}