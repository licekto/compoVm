#include "nodes/compo/port.h"

namespace nodes {

	namespace compo {

		CPort::CPort(std::shared_ptr<nodes::procedural::CSymbol> name, bool atomic)
			:   CNode(types::nodeType::PORT),
			    m_name(name), m_atomic(atomic) {
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

		bool CPort::getAtomic() const {
			return m_atomic;
		}

	}

}