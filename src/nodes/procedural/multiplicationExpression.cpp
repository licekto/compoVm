#include "nodes/procedural/multiplicationExpression.h"

namespace nodes {

	namespace procedural {

		CMultiplicationExpression::CMultiplicationExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::MULTIPLICATION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::TIMES, op1, op2) {
		}
	}

}