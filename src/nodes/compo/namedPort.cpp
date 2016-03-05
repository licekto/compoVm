#include "nodes/compo/namedPort.h"

namespace nodes {

	namespace compo {

		CNamedPort::CNamedPort(std::shared_ptr<nodes::procedural::CSymbol> name,
		                       bool atomicity,
		                       std::shared_ptr<nodes::procedural::CSymbol> nameParam,
		                       bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::NAMED, name, atomicity, collectivity),
			    m_nameParam(nameParam) {
		}

		void CNamedPort::print(std::ostream& outstream) const {
			outstream << "signaturesPort" << std::endl;
		}

		std::shared_ptr<nodes::procedural::CSymbol> CNamedPort::getParamName() const {
			return m_nameParam;
		}
	}

}