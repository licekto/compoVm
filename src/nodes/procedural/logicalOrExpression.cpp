#include "nodes/procedural/logicalOrExpression.h"

namespace nodes {

	namespace procedural {

		CLogicalOrExpression::CLogicalOrExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LOGICAL_OR_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LOGICAL_OR, op1, op2) {
		}
	}

}