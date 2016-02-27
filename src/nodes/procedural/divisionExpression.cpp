#include "nodes/procedural/divisionExpression.h"

namespace nodes {

	namespace procedural {

		CDivisionExpression::CDivisionExpression( std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::DIVISION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::DIVISION, op1, op2) {
		}
	}

}