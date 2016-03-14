#include "ast/compo/serviceInvocation.h"

namespace ast {

	namespace compo {

		CServiceInvocation::CServiceInvocation(std::shared_ptr<ast::procedural::CSymbol> receiver,
		                                       std::shared_ptr<ast::procedural::CSymbol> selector,
		                                       std::shared_ptr<ast::CNode> parameters)
			:   CNode(types::nodeType::SERVICE_INVOCATION),
			    m_receiver(receiver),
			    m_selector(selector),
			    m_parameters(parameters) {
		}

		void CServiceInvocation::print(std::ostream& outstream) const {
			outstream << "&" << *m_selector << std::endl;
		}


		std::shared_ptr<ast::procedural::CSymbol> CServiceInvocation::getReceiverName() const {
			return m_receiver;
		}

		std::shared_ptr<ast::procedural::CSymbol> CServiceInvocation::getSelectorName() const {
			return m_selector;
		}

		std::shared_ptr<ast::CNode> CServiceInvocation::getParameters() const {
			return m_parameters;
		}
	}

}