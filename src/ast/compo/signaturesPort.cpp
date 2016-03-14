#include "ast/compo/port.h"
#include "ast/compo/signaturesPort.h"

namespace ast {

	namespace compo {

		CSignaturesPort::CSignaturesPort(std::shared_ptr<ast::procedural::CSymbol> name,
		                                 bool atomicity,
		                                 std::vector<std::shared_ptr<ast::compo::CServiceSignature>> list,
		                                 bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::EXPLICIT_LIST, name, atomicity, collectivity),
			    m_signaturesList(list) {
		}

		void CSignaturesPort::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		size_t CSignaturesPort::getSignaturesSize() const {
			return m_signaturesList.size();
		}

		std::shared_ptr<ast::compo::CServiceSignature> CSignaturesPort::getSignatureAt(unsigned int index) const {
			std::shared_ptr<ast::compo::CServiceSignature> signature = nullptr;
			try {
				signature = m_signaturesList.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return signature;
		}
	}

}