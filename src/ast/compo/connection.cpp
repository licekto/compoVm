#include "ast/compo/connection.h"

namespace ast {

	namespace compo {

		CConnection::CConnection(std::shared_ptr<ast::compo::CPortAddress> portIdentification1,
		                         std::shared_ptr<ast::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::CONNECTION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CConnection::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portIdentification1 << " : { }";
		}
	}

}