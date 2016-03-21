#include "ast/nodes/procedural/forStatement.h"
#include "ast/nodes/procedural/whileStatement.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CWhileStatement::CWhileStatement(   std::shared_ptr<ast::nodes::procedural::CAbstractExpression> cond,
			                                    std::shared_ptr<ast::nodes::procedural::CCompoundBody> body)
				:   CNode(types::nodeType::WHILE),
				    m_condition(cond),
				    m_body(body) {
			}

			void CWhileStatement::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CCompoundBody> CWhileStatement::getBody() const {
				return m_body;
			}

			std::shared_ptr<ast::nodes::procedural::CAbstractExpression> CWhileStatement::getCondition() const {
				return m_condition;
			}

		}
	}
}