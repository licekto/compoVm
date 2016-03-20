#include "ast/nodes/procedural/forStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CForStatement::CForStatement(   std::shared_ptr<ast::nodes::procedural::CAssignmentExpression> initExpression,
		                                std::shared_ptr<ast::nodes::procedural::CAbstractExpression> condition,
		                                std::shared_ptr<ast::nodes::procedural::CAbstractExpression> increment,
		                                std::shared_ptr<ast::nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::FOR),
			    m_initExpression(initExpression),
			    m_condition(condition),
			    m_increment(increment),
			    m_body(body) {
		}

		void CForStatement::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CCompoundBody> CForStatement::getBody() const {
			return m_body;
		}

		std::shared_ptr<ast::nodes::procedural::CAssignmentExpression> CForStatement::getInitExpression() const {
			return m_initExpression;
		}

		std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CForStatement::getCondition() const {
			return m_condition;
		}

		std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CForStatement::getIncrement() const  {
			return m_increment;
		}

	}
    }
}