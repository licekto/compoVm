#include "nodes/compo/port.h"
#include "nodes/compo/signaturesPort.h"

namespace nodes {

	namespace compo {

		CSignaturesPort::CSignaturesPort(std::shared_ptr<nodes::procedural::CSymbol> name,
		                                 bool atomicity,
		                                 std::vector<std::shared_ptr<nodes::compo::CServiceSignature>> list,
		                                 bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::EXPLICIT_LIST, name, atomicity, collectivity),
			    m_signaturesList(list) {
		}

		void CSignaturesPort::print(std::ostream& outstream) const {
			outstream << "signaturesPort" << std::endl;
		}

		size_t CSignaturesPort::getSignaturesSize() const {
			return m_signaturesList.size();
		}

		std::shared_ptr<nodes::compo::CServiceSignature> CSignaturesPort::getSignatureAt(unsigned int index) const {
			std::shared_ptr<nodes::compo::CServiceSignature> signature = nullptr;
			try {
				signature = m_signaturesList.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return signature;
		}
	}

}