#include "nodes/procedural/additionExpression.h"

namespace nodes {

	namespace procedural {

		CAdditionExpression::CAdditionExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ADDITION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::PLUS, op1, op2) {
		}
	}

}