#include "nodes/compo/portAddress.h"

namespace nodes {

	namespace compo {

		CPortAddress::CPortAddress(std::shared_ptr<nodes::procedural::CSymbol> portName,
                                           std::shared_ptr<nodes::CNode> component)
			:   CNode(types::nodeType::PORT_ADDRESS),
			    m_portName(portName), m_component(component) {
		}

		void CPortAddress::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_portName << " : { }";
		}

		std::shared_ptr<nodes::procedural::CSymbol> CPortAddress::getPortName() const {
                    return m_portName;
                }
                
                std::shared_ptr<nodes::CNode> CPortAddress::getComponent() const {
                    return m_component;
                }
	}

}