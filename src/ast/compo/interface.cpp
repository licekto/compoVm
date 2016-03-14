#include "ast/compo/interface.h"

namespace ast {

	namespace compo {

		CInterface::CInterface(std::shared_ptr<ast::procedural::CSymbol> name,
		                       std::shared_ptr<ast::procedural::CSymbol> extends,
		                       std::vector<std::shared_ptr<ast::compo::CServiceSignature>> list)
			:   CNode(types::nodeType::INTERFACE),
			    m_name(name),
			    m_extends(extends),
			    m_signaturesList(list) {
		}

		void CInterface::print(std::ostream& outstream) const {
			outstream << "signaturesPort" << std::endl;
		}

		std::shared_ptr<ast::procedural::CSymbol> CInterface::getName() const {
			return m_name;
		}

		std::shared_ptr<ast::procedural::CSymbol> CInterface::getExtends() const {
			return m_extends;
		}

		size_t CInterface::getSignaturesSize() const {
			return m_signaturesList.size();
		}

		std::shared_ptr<ast::compo::CServiceSignature> CInterface::getSignatureAt(unsigned int index) const {
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