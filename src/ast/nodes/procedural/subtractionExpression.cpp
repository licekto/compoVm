#include "ast/nodes/procedural/subtractionExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CSubtractionExpression::CSubtractionExpression( std::shared_ptr<ast::nodes::CNode> op1,
			        std::shared_ptr<ast::nodes::CNode> op2)
				:   CNode(types::nodeType::SUBTRACTION_EXPRESSION),
				    CAbstractExpression(),
				    CBinaryExpression(types::operatorType::MINUS, op1, op2) {
			}

			void CSubtractionExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}