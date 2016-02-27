#include "nodes/procedural/logicalAndExpression.h"

namespace nodes {

	namespace procedural {

		CLogicalAndExpression::CLogicalAndExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LOGICAL_AND_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LOGICAL_AND, op1, op2) {
		}
	}

}