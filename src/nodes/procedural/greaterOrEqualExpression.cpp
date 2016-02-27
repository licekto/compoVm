#include "nodes/procedural/greaterOrEqualExpression.h"

namespace nodes {

	namespace procedural {

		CGreaterOrEqualExpression::CGreaterOrEqualExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::GREATER_OR_EQUAL_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::GREATER_OR_EQUAL, op1, op2) {
		}
	}

}