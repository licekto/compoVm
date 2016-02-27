#include "nodes/procedural/equalityExpression.h"

namespace nodes {

	namespace procedural {

		CEqualityExpression::CEqualityExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::EQUALITY, op1, op2) {
		}
	}

}