#include "nodes/compo/bind.h"

namespace nodes {

	namespace compo {

		CBind::CBind(std::shared_ptr<nodes::compo::CPortAddress> portIdentification1,
                             std::shared_ptr<nodes::compo::CPortAddress> portIdentification2)
			:   CNode(types::nodeType::CONNECTION),
			    m_portIdentification1(portIdentification1), m_portIdentification2(portIdentification2) {
		}

		void CBind::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portIdentification1 << " : { }";
		}

		std::shared_ptr<nodes::compo::CPortAddress> CBind::getPortIdentification1() const {
                    return m_portIdentification1;
                }
                
                std::shared_ptr<nodes::compo::CPortAddress> CBind::getPortIdentification2() const {
                    return m_portIdentification2;
                }
	}

}