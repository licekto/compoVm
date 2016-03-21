#include "ast/nodes/procedural/assignmentExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CAssignmentExpression::CAssignmentExpression(std::shared_ptr<ast::nodes::procedural::CSymbol> variable, std::shared_ptr<ast::nodes::CNode> rVal)
				:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
				    CAbstractExpression(),
				    m_variable(variable), m_rValue(rVal) {
			}

			void CAssignmentExpression::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CAssignmentExpression::getVariable() const {
				return m_variable;
			}

			std::shared_ptr<ast::nodes::CNode> CAssignmentExpression::getRValue() const {
				return m_rValue;
			}

		}
	}
}