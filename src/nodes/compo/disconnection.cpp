#include "nodes/compo/disconnection.h"

namespace nodes {

	namespace compo {

		CDisconnection::CDisconnection(std::shared_ptr<nodes::compo::CPortAddress> portIdentification1,
                                               std::shared_ptr<nodes::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::DISCONNECTION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CDisconnection::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portIdentification1 << " : { }";
		}
	}

}