#include "ast/nodes/procedural/returnStatement.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CReturnStatement::CReturnStatement(std::shared_ptr<CNode> expression)
				:   CNode(types::nodeType::RETURN),
				    m_expression(expression) {
			}

			void CReturnStatement::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<CNode> CReturnStatement::getExpression() const {
				return m_expression;
			}

		}
	}
}