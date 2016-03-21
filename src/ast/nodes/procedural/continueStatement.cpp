#include "ast/nodes/procedural/continueStatement.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			CContinueStatement::CContinueStatement()
				:   CNode(types::nodeType::CONTINUE) {
			}

			void CContinueStatement::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}