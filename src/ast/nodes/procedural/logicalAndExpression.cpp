#include "ast/nodes/procedural/logicalAndExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CLogicalAndExpression::CLogicalAndExpression( std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op1,
			        std::shared_ptr<ast::nodes::procedural::CAbstractExpression> op2)
				:   CNode(types::nodeType::LOGICAL_AND_EXPRESSION),
				    CAbstractExpression(),
				    CBinaryExpression(types::operatorType::LOGICAL_AND, op1, op2) {
			}

			void CLogicalAndExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}