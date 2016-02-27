#include "nodes/procedural/subtractionExpression.h"

namespace nodes {

	namespace procedural {

		CSubtractionExpression::CSubtractionExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::SUBTRACTION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::MINUS, op1, op2) {
		}
	}

}