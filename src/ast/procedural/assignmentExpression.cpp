#include "ast/procedural/assignmentExpression.h"

namespace ast {

	namespace procedural {

		CAssignmentExpression::CAssignmentExpression(std::shared_ptr<ast::procedural::CSymbol> variable, std::shared_ptr<ast::CNode> rVal)
			:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
			    CAbstractExpression(),
			    m_variable(variable), m_rValue(rVal) {
		}

		void CAssignmentExpression::print(std::ostream& outstream) const {
			outstream << *m_variable << " := " << *m_rValue << ";" << std::endl;
		}

		std::shared_ptr<ast::procedural::CSymbol> CAssignmentExpression::getVariable() const {
			return m_variable;
		}

		std::shared_ptr<ast::CNode> CAssignmentExpression::getRValue() const {
			return m_rValue;
		}

	}

}