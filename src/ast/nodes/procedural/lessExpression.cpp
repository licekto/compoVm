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

			void CLessExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}