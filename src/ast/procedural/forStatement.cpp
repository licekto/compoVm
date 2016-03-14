#include "ast/procedural/forStatement.h"

namespace ast {

	namespace procedural {

		CForStatement::CForStatement(   std::shared_ptr<ast::procedural::CAssignmentExpression> initExpression,
		                                std::shared_ptr<ast::procedural::CAbstractExpression> condition,
		                                std::shared_ptr<ast::procedural::CAbstractExpression> increment,
		                                std::shared_ptr<ast::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::FOR),
			    m_initExpression(initExpression),
			    m_condition(condition),
			    m_increment(increment),
			    m_body(body) {
		}

		void CForStatement::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		std::shared_ptr<ast::procedural::CCompoundBody> CForStatement::getBody() const {
			return m_body;
		}

		std::shared_ptr<ast::procedural::CAssignmentExpression> CForStatement::getInitExpression() const {
			return m_initExpression;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CForStatement::getCondition() const {
			return m_condition;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CForStatement::getIncrement() const  {
			return m_increment;
		}

	}

}