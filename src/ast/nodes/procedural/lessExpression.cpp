#include "ast/nodes/procedural/lessExpression.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CLessExpression::CLessExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		                                  std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::LESS_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::LESS, op1, op2) {
		}

		void CLessExpression::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}