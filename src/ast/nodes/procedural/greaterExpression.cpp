#include "ast/nodes/procedural/greaterExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CGreaterExpression::CGreaterExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		                                        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::GREATER_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::GREATER, op1, op2) {
		}

		void CGreaterExpression::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}