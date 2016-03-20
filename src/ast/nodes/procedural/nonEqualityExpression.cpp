#include "ast/nodes/procedural/nonEqualityExpression.h"

namespace ast {

    namespace nodes {

	namespace procedural {

		CNonEqualityExpression::CNonEqualityExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
		        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::NON_EQUALITY_EXPRESSION),
			    CAbstractExpression(),
			    CBinaryExpression(types::operatorType::NON_EQUALITY, op1, op2) {
		}

		void CNonEqualityExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}
	}
    }
}