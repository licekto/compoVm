#include "ast/nodes/procedural/continueStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CContinueStatement::CContinueStatement()
			:   CNode(types::nodeType::CONTINUE) {
		}

		void CContinueStatement::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}