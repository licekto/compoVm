#include "nodes/compo/serviceInvocation.h"

namespace nodes {

	namespace compo {

		CServiceInvocation::CServiceInvocation(std::shared_ptr<nodes::procedural::CSymbol> receiver,
                                                       std::shared_ptr<nodes::procedural::CSymbol> selector,
                                                       std::shared_ptr<nodes::CNode> parameters)
			:   CNode(types::nodeType::SERVICE_INVOCATION),
			    m_receiver(receiver),
                            m_selector(selector),
                            m_parameters(parameters) {
		}

		void CServiceInvocation::print(std::ostream& outstream) const {
			outstream << "&" << *m_selector << std::endl;
		}

                
		std::shared_ptr<nodes::procedural::CSymbol> CServiceInvocation::getReceiverName() const {
			return m_receiver;
		}
                
                std::shared_ptr<nodes::procedural::CSymbol> CServiceInvocation::getSelectorName() const {
			return m_selector;
		}
                
                std::shared_ptr<nodes::CNode> CServiceInvocation::getParameters() const {
                        return m_parameters;
                }
	}

}