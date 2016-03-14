#include "ast/procedural/divisionExpression.h"

namespace ast {

	namespace procedural {

		CDivisionExpression::CDivisionExpression( std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::DIVISION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::DIVISION, op1, op2) {
		}
	}

}