#include "ast/nodes/procedural/lessOrEqualExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CLessOrEqualExpression::CLessOrEqualExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
			        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
				:   CNode(types::nodeType::LESS_OR_EQUAL_EXPRESSION),
				    CAbstractExpression(),
				    CBinaryExpression(types::operatorType::LESS_OR_EQUAL, op1, op2) {
			}

			void CLessOrEqualExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}