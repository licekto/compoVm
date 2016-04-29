#include "ast/nodes/compo/interface.h"
#include "logger/logger.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CInterface::CInterface(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                       std::shared_ptr<ast::nodes::procedural::CSymbol> extends,
			                       std::vector<std::shared_ptr<ast::nodes::compo::CServiceSignature>> list)
				:   CNode(types::nodeType::INTERFACE),
				    CAbstractDescriptorInterface(name, extends),
				    m_signaturesList(list) {
			}

			void CInterface::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			size_t CInterface::getSignaturesSize() const {
				return m_signaturesList.size();
			}

			std::shared_ptr<ast::nodes::compo::CServiceSignature> CInterface::getSignatureAt(unsigned int index) const {
				std::shared_ptr<ast::nodes::compo::CServiceSignature> signature = nullptr;
				try {
					signature = m_signaturesList.at(index);
				} catch (const std::out_of_range& ex) {
					TRACE(ERROR, ex.what());
				}
				return signature;
			}
		}
	}
}