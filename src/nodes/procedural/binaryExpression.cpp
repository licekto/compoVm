#include "nodes/procedural/binaryExpression.h"

namespace nodes {

	namespace procedural {

		CBinaryExpression::CBinaryExpression(types::operatorType type,
		                                     std::shared_ptr<nodes::procedural::CAbstractExpression> op1,
		                                     std::shared_ptr<nodes::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
			    CAbstractExpression(),
			    m_operator(type),
			    m_operand1(op1),
			    m_operand2(op2) {
		}

		void CBinaryExpression::print(std::ostream& outstream) const {
			outstream << *m_operand1 << " " << m_operator << *m_operand2 << ";" << std::endl;
		}

		types::operatorType CBinaryExpression::getOperator() const {
			return m_operator;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CBinaryExpression::getOperand1() const {
			return m_operand1;
		}

		std::shared_ptr<nodes::procedural::CAbstractExpression> CBinaryExpression::getOperand2() const {
			return m_operand2;
		}
	}

}