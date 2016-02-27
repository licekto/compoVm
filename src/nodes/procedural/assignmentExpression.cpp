#include "nodes/procedural/assignmentExpression.h"

namespace nodes {

	namespace procedural {

		CAssignmentExpression::CAssignmentExpression(CSymbol * variable, CNode * rVal)
			:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
			    m_variable(variable), m_rValue(rVal) {
		}

		CAssignmentExpression::CAssignmentExpression(const CAssignmentExpression& other)
			: CNode(other),
			  m_variable(new CSymbol(*other.m_variable)),
			  m_rValue(other.m_rValue->clone()) {
		}

		CAssignmentExpression::CAssignmentExpression(CAssignmentExpression&& other) noexcept
			: CNode(std::move(other)),
			  m_variable(new CSymbol(std::move(*other.m_variable))),
			  m_rValue(other.m_rValue) {
			other.m_rValue = nullptr;
		}

		CAssignmentExpression& CAssignmentExpression::operator =(const CAssignmentExpression& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_variable = new CSymbol(*other.m_variable);
				this->m_rValue = other.m_rValue->clone();
			}

			return *this;
		}

		CAssignmentExpression& CAssignmentExpression::operator =(CAssignmentExpression&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_variable = new CSymbol(std::move(*other.m_variable));
				this->m_rValue = other.m_rValue;
				other.m_rValue = nullptr;
			}

			return *this;
		}

		CNode * CAssignmentExpression::clone() const {
			return new CAssignmentExpression(*this);
		}

		CAssignmentExpression::~CAssignmentExpression() {
			delete m_variable;
			delete m_rValue;
		}

		void CAssignmentExpression::print(std::ostream& outstream) const {
			outstream << *m_variable << " := " << *m_rValue << ";" << std::endl;
		}

		CSymbol * CAssignmentExpression::getVariable() const {
			return m_variable;
		}

		CNode * CAssignmentExpression::getRValue() const {
			return m_rValue;
		}

	}

}