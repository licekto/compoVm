#include "ast/nodes/compo/disconnection.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CDisconnection::CDisconnection(std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification1,
		                               std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::DISCONNECTION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CDisconnection::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}
	}
    }
}