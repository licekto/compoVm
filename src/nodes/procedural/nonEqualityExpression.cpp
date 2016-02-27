#include "nodes/procedural/nonEqualityExpression.h"

namespace nodes {

	namespace procedural {

		CNonEqualityExpression::CNonEqualityExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::NON_EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::NON_EQUALITY, op1, op2) {
		}
	}

}