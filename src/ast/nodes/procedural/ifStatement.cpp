#include "ast/nodes/procedural/ifStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CIfStatement::CIfStatement(std::shared_ptr<ast::nodes::procedural::CAbstractExpression> condition,
		                           std::shared_ptr<ast::nodes::procedural::CCompoundBody> ifBody,
		                           std::shared_ptr<ast::nodes::procedural::CCompoundBody> elseBody)
			:   CNode(types::nodeType::IF),
			    m_condition(condition),
			    m_ifBody(ifBody),
			    m_elseBody(elseBody) {
		}

		void CIfStatement::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CCompoundBody> CIfStatement::getIfBody() const {
			return m_ifBody;
		}

		std::shared_ptr<ast::nodes::procedural::CCompoundBody> CIfStatement::getElseBody() const {
			return m_elseBody;
		}

		std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CIfStatement::getCondition() const {
			return m_condition;
		}

	}
    }
}