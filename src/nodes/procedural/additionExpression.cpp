#include "nodes/procedural/additionExpression.h"
#include "nodes/procedural/binaryExpression.h"

namespace nodes {

	namespace procedural {

		CAdditionExpression::CAdditionExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ADDITIVE_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::PLUS, op1, op2) {
		}
	}

}