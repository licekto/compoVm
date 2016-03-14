#include "ast/compo/delegation.h"

namespace ast {

	namespace compo {

		CDelegation::CDelegation(std::shared_ptr<ast::compo::CPortAddress> portIdentification1,
		                         std::shared_ptr<ast::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::DELEGATION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CDelegation::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}

}