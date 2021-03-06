#include "ast/nodes/procedural/binaryExpression.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CBinaryExpression::CBinaryExpression(types::operatorType type,
			                                     std::shared_ptr<ast::nodes::CNode> op1,
			                                     std::shared_ptr<ast::nodes::CNode> op2)
				:   CAbstractExpression(),
				    m_operator(type),
				    m_operand1(op1),
				    m_operand2(op2) {
			}

			types::operatorType CBinaryExpression::getOperator() const {
				return m_operator;
			}

			std::shared_ptr<ast::nodes::CNode> CBinaryExpression::getOperand1() const {
				return m_operand1;
			}

			std::shared_ptr<ast::nodes::CNode> CBinaryExpression::getOperand2() const {
				return m_operand2;
			}
		}
	}
}