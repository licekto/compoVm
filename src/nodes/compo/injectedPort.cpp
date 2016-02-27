#include "nodes/compo/injectedPort.h"

namespace nodes {

	namespace compo {

		CInjectedPort::CInjectedPort( std::shared_ptr<nodes::procedural::CSymbol> name,
		                              bool atomic,
		                              std::shared_ptr<nodes::procedural::CSymbol> injectedWith  )
			:   CNode(types::nodeType::INJECTED_PORT),
			    CPort(name, atomic),
			    m_injectedWith(injectedWith) {
		}

		void CInjectedPort::print(std::ostream& outstream) const {
			outstream << "\t";
			outstream << *m_name << " : { }";
		}

		std::string CInjectedPort::getInjectedWith() const {
			if (m_injectedWith) {
				return m_injectedWith->getStringValue();
			}
			return "";
		}
	}

}