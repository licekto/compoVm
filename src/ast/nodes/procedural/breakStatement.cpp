#include "ast/nodes/procedural/breakStatement.h"

namespace ast {

    namespace nodes {
    
	namespace procedural {

		CBreakStatement::CBreakStatement()
			:   CNode(types::nodeType::BREAK) {
		}

		void CBreakStatement::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}
	}
    }
}