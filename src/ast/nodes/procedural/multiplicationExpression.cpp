#include "ast/nodes/procedural/multiplicationExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CMultiplicationExpression::CMultiplicationExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::MULTIPLICATION_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::TIMES, op1, op2) {
		}

		void CMultiplicationExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}
	}
    }
}