#include "ast/procedural/binaryExpression.h"

namespace ast {

	namespace procedural {

		CBinaryExpression::CBinaryExpression(types::operatorType type,
		                                     std::shared_ptr<ast::procedural::CAbstractExpression> op1,
		                                     std::shared_ptr<ast::procedural::CAbstractExpression> op2)
			:   CNode(types::nodeType::ASSIGNMENT_EXPRESSION),
			    CAbstractExpression(),
			    m_operator(type),
			    m_operand1(op1),
			    m_operand2(op2) {
		}

		void CBinaryExpression::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		types::operatorType CBinaryExpression::getOperator() const {
			return m_operator;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CBinaryExpression::getOperand1() const {
			return m_operand1;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CBinaryExpression::getOperand2() const {
			return m_operand2;
		}
	}

}