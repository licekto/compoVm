#include "ast/nodes/procedural/divisionExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CDivisionExpression::CDivisionExpression( std::shared_ptr<ast::nodes::CNode> op1,
			        std::shared_ptr<ast::nodes::CNode> op2)
				:   CNode(types::nodeType::DIVISION_EXPRESSION),
				    CAbstractExpression(),
				    CBinaryExpression(types::operatorType::DIVISION, op1, op2) {
			}

			void CDivisionExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}