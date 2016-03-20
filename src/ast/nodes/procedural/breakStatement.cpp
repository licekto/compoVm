#include "ast/nodes/procedural/breakStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CBreakStatement::CBreakStatement()
			:   CNode(types::nodeType::BREAK) {
		}

		void CBreakStatement::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}