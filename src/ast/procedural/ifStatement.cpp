#include "ast/procedural/ifStatement.h"

namespace ast {

	namespace procedural {

		CIfStatement::CIfStatement(std::shared_ptr<ast::procedural::CAbstractExpression> condition,
		                           std::shared_ptr<ast::procedural::CCompoundBody> ifBody,
		                           std::shared_ptr<ast::procedural::CCompoundBody> elseBody)
			:   CNode(types::nodeType::IF),
			    m_condition(condition),
			    m_ifBody(ifBody),
			    m_elseBody(elseBody) {
		}

		void CIfStatement::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::procedural::CCompoundBody> CIfStatement::getIfBody() const {
			return m_ifBody;
		}

		std::shared_ptr<ast::procedural::CCompoundBody> CIfStatement::getElseBody() const {
			return m_elseBody;
		}

		std::shared_ptr<ast::procedural::CAbstractExpression> CIfStatement::getCondition() const {
			return m_condition;
		}

	}

}