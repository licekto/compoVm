#include "ast/nodes/compo/connection.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CConnection::CConnection(std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification1,
		                         std::shared_ptr<ast::nodes::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::CONNECTION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CConnection::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}