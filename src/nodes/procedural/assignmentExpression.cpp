#include "nodes/procedural/assignmentExpression.h"

namespace nodes {

	namespace procedural {

		CAssignmentExpression::CAssignmentExpression(std::shared_ptr<nodes::procedural::CSymbol> variable, std::shared_ptr<nodes::CNode> rVal)
			:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
			    m_variable(variable), m_rValue(rVal) {
		}

		void CAssignmentExpression::print(std::ostream& outstream) const {
			outstream << *m_variable << " := " << *m_rValue << ";" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CAssignmentExpression::getVariable() const {
			return m_variable;
		}

		std::shared_ptr<nodes::CNode> CAssignmentExpression::getRValue() const {
			return m_rValue;
		}

	}

}