#include "nodes/compo/port.h"

namespace nodes {

	namespace compo {

		CPort::CPort(nodes::types::portType type, std::shared_ptr<nodes::procedural::CSymbol> name, bool atomicity, bool collectivity)
			:   CNode(types::nodeType::PORT),
			    m_portType(type),
			    m_name(name),
			    m_atomicity(atomicity),
                            m_collectivity(collectivity){
		}

		void CPort::print(std::ostream& outstream) const {
			if (m_name) {
				outstream << "\t";
				outstream << *m_name << " : { }";
			}
		}

		std::string CPort::getName() const {
			if (m_name) {
				return m_name->getStringValue();
			}
			return "";
		}

		bool CPort::getAtomicity() const {
			return m_atomicity;
		}

		nodes::types::portType CPort::getPortType() const {
			return m_portType;
		}

		void CPort::setKindOf(std::shared_ptr<nodes::procedural::CSymbol> kindOf) {
			m_kindOf = kindOf;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CPort::getKindOf() const {
			return m_kindOf;
		}
                
                bool CPort::getCollectivity() const {
			return m_collectivity;
		}
	}

}