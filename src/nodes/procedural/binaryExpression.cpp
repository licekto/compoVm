#include "nodes/procedural/assignment.h"
#include "nodes/types/operatorType.h"
#include "nodes/procedural/binaryExpression.h"

namespace nodes {

	namespace procedural {

		CBinaryExpression::CBinaryExpression(types::operatorType type,
		                                     CAbstractPrimaryExpression * op1,
		                                     CAbstractPrimaryExpression * op2)
			:   CNode(types::nodeType::ASSIGNMENT),
			    CAbstractExpression(),
			    m_operator(type),
			    m_operand1(op1),
			    m_operand2(op2) {
		}

		CBinaryExpression::CBinaryExpression(const CBinaryExpression& other)
			:   CNode(other),
			    CAbstractExpression(),
			    m_operator(other.m_operator),
			    m_operand1(other.m_operand1),
			    m_operand2(other.m_operand2) {
		}

		CBinaryExpression::CBinaryExpression(CBinaryExpression&& other) noexcept
			:   CNode(std::move(other)),
			    CAbstractExpression(),
			    m_operator(std::move(other.m_operator)),
			    m_operand1(std::move(other.m_operand1)),
			    m_operand2(std::move(other.m_operand2)) {
			other.m_operand1 = nullptr;
			other.m_operand2 = nullptr;
		}

		CBinaryExpression& CBinaryExpression::operator =(const CBinaryExpression& other) {
			if (&other != this) {
				this->m_nodeType = other.m_nodeType;
				this->m_operator = other.m_operator;
				this->m_operand1 = other.m_operand1;
				this->m_operand2 = other.m_operand2;
			}

			return *this;
		}

		CBinaryExpression& CBinaryExpression::operator =(CBinaryExpression&& other) noexcept {
			if (&other != this) {
				this->m_nodeType = std::move(other.m_nodeType);
				this->m_operator = std::move(other.m_operator);
				this->m_operand1 = std::move(other.m_operand1);
				this->m_operand2 = std::move(other.m_operand2);
			}

			return *this;
		}

		CNode * CBinaryExpression::clone() const {
			return new CBinaryExpression(*this);
		}

		CBinaryExpression::~CBinaryExpression() {
			delete m_operand1;
			delete m_operand2;
		}

		void CBinaryExpression::print(std::ostream& outstream) const {
			outstream << *m_operand1 << " " << m_operator << *m_operand2 << ";" << std::endl;
		}

		types::operatorType CBinaryExpression::getOperator() const {
			return m_operator;
		}

		CAbstractPrimaryExpression * CBinaryExpression::getOperand1() const {
			return m_operand1;
		}

		CAbstractPrimaryExpression * CBinaryExpression::getOperand2() const {
			return m_operand2;
		}
	}

}