#include "ast/nodes/compo/serviceInvocation.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CServiceInvocation::CServiceInvocation(std::shared_ptr<ast::nodes::procedural::CSymbol> receiver,
		                                       std::shared_ptr<ast::nodes::procedural::CSymbol> selector,
		                                       std::shared_ptr<ast::nodes::CNode> parameters)
			:   CNode(types::nodeType::SERVICE_INVOCATION),
			    m_receiver(receiver),
			    m_selector(selector),
			    m_parameters(parameters) {
		}

		void CServiceInvocation::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
			visitor->visit(shared_from_this());
		}


		std::shared_ptr<ast::nodes::procedural::CSymbol> CServiceInvocation::getReceiverName() const {
			return m_receiver;
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CServiceInvocation::getSelectorName() const {
			return m_selector;
		}

		std::shared_ptr<ast::nodes::CNode> CServiceInvocation::getParameters() const {
			return m_parameters;
		}
	}
    }
}