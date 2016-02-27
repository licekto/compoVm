#include "nodes/procedural/additiveExpression.h"
#include "nodes/procedural/binaryExpression.h"

namespace nodes {

	namespace procedural {

		CAdditiveExpression::CAdditiveExpression( CAbstractExpression * op1,
                                                          CAbstractExpression * op2)
			:   CNode(types::nodeType::ADDITIVE_EXPRESSION),
			    CAbstractExpression(),
                            CBinaryExpression(types::operatorType::PLUS, op1, op2) {
		}

		CAdditiveExpression::CAdditiveExpression(const CAdditiveExpression& other)
			:   CNode(other),
			    CAbstractExpression(),
			    CBinaryExpression(other.m_operator, other.m_operand1, other.m_operand2) {
		}

		CAdditiveExpression::CAdditiveExpression(CAdditiveExpression&& other) noexcept
			:   CNode(std::move(other)),
			    CAbstractExpression(),
                            CBinaryExpression(std::move(other.m_operator), std::move(other.m_operand1), std::move(other.m_operand2)) {
			other.m_operand1 = nullptr;
			other.m_operand2 = nullptr;
		}

		CAdditiveExpression& CAdditiveExpression::operator =(const CAdditiveExpression& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_operator = other.m_operator;
				this->m_operand1 = other.m_operand1;
				this->m_operand2 = other.m_operand2;
			}

			return *this;
		}

		CAdditiveExpression& CAdditiveExpression::operator =(CAdditiveExpression&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_operator = std::move(other.m_operator);
				this->m_operand1 = std::move(other.m_operand1);
				this->m_operand2 = std::move(other.m_operand2);
			}

			return *this;
		}

		CNode * CAdditiveExpression::clone() const {
			return new CAdditiveExpression(*this);
		}

		CAdditiveExpression::~CAdditiveExpression() {
		}
	}

}