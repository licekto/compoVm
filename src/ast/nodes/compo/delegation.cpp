#include "ast/nodes/compo/delegation.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CDelegation::CDelegation(std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification1,
			                         std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification2)
				:   CNode(types::nodeType::DELEGATION),
				    CBind(portIdentification1, portIdentification2) {
			}

			void CDelegation::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}