#include "nodes/compo/universalPort.h"

namespace nodes {

	namespace compo {

		CUniversalPort::CUniversalPort(std::shared_ptr<nodes::procedural::CSymbol> name,
		                               bool atomicity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::UNIVERSAL, name, atomicity) {
		}

		void CUniversalPort::print(std::ostream& outstream) const {
			outstream << "signaturesPort" << std::endl;
		}
	}

}