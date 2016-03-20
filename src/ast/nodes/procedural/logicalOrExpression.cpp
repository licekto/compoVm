#include "ast/nodes/procedural/logicalOrExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CLogicalOrExpression::CLogicalOrExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LOGICAL_OR_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LOGICAL_OR, op1, op2) {
		}

		void CLogicalOrExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}
	}
    }
}