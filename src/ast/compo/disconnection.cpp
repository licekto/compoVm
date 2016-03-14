#include "ast/compo/disconnection.h"

namespace ast {

	namespace compo {

		CDisconnection::CDisconnection(std::shared_ptr<ast::compo::CPortAddress> portIdentification1,
		                               std::shared_ptr<ast::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::DISCONNECTION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CDisconnection::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }
	}

}