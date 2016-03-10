#include "nodes/compo/delegation.h"

namespace nodes {

	namespace compo {

		CDelegation::CDelegation(std::shared_ptr<nodes::compo::CPortAddress> portIdentification1,
		                         std::shared_ptr<nodes::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::DELEGATION),
			    CBind(portIdentification1, portIdentification2) {
		}

		void CDelegation::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portIdentification1 << " : { }";
		}
	}

}