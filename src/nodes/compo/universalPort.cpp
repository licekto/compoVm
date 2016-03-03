#include "nodes/compo/universalPort.h"

namespace nodes {

	namespace compo {

		CUniversalPort::CUniversalPort(std::shared_ptr<nodes::procedural::CSymbol> name,
		                               bool atomicity,
                                               bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::UNIVERSAL, name, atomicity, collectivity) {
		}

		void CUniversalPort::print(std::ostream& outstream) const {
			outstream << "signaturesPort" << std::endl;
		}
	}

}