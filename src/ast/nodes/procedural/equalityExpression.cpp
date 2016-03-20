#include "ast/nodes/procedural/equalityExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CEqualityExpression::CEqualityExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::EQUALITY, op1, op2) {
		}

		void CEqualityExpression::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}