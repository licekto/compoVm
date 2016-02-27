#include "nodes/procedural/lessExpression.h"

namespace nodes {

	namespace procedural {

		CLessExpression::CLessExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LESS_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LESS, op1, op2) {
		}
	}

}