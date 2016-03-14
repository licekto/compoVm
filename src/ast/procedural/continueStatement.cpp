#include "ast/procedural/continueStatement.h"

namespace ast {

	namespace procedural {

		CContinueStatement::CContinueStatement()
			:   CNode(types::nodeType::CONTINUE) {
		}

		void CContinueStatement::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }
	}

}