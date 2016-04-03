#include "ast/nodes/compo/port.h"
#include "ast/nodes/compo/signaturesPort.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CSignaturesPort::CSignaturesPort(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                                 bool atomicity,
                                                         bool collectivity,
                                                         nodes::types::visibilityType visibility,
                                                         nodes::types::portRoleType role,
			                                 std::vector<std::shared_ptr<ast::nodes::compo::CServiceSignature>> list)
				:   CNode(types::nodeType::SIGNATURES_PORT),
				    CPort(types::portType::EXPLICIT_LIST, name, atomicity, collectivity, visibility, role),
				    m_signaturesList(list) {
			}

			void CSignaturesPort::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CSignaturesPort::getSignaturesSize() const {
				return m_signaturesList.size();
			}

			std::shared_ptr<ast::nodes::compo::CServiceSignature> CSignaturesPort::getSignatureAt(unsigned int index) const {
				std::shared_ptr<ast::nodes::compo::CServiceSignature> signature = nullptr;
				try {
					signature = m_signaturesList.at(index);
				} catch (const std::out_of_range& ex) {
					// log error message
				}
				return signature;
			}
		}
	}
}