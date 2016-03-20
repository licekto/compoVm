#include "ast/nodes/procedural/additionExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CAdditionExpression::CAdditionExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ADDITION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::PLUS, op1, op2) {
		}

		void CAdditionExpression::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}