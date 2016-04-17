#include "ast/nodes/procedural/greaterOrEqualExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CGreaterOrEqualExpression::CGreaterOrEqualExpression( std::shared_ptr<ast::nodes::CNode> op1,
			        std::shared_ptr<ast::nodes::CNode> op2)
				:   CNode(types::nodeType::GREATER_OR_EQUAL_EXPRESSION),
				    CAbstractExpression(),
				    CBinaryExpression(types::operatorType::GREATER_OR_EQUAL, op1, op2) {
			}

			void CGreaterOrEqualExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}