#include "ast/procedural/breakStatement.h"

namespace ast {

	namespace procedural {

		CBreakStatement::CBreakStatement()
			:   CNode(types::nodeType::BREAK) {
		}

		void CBreakStatement::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}