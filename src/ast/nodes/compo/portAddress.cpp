#include "ast/nodes/compo/portAddress.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CPortAddress::CPortAddress(std::shared_ptr<ast::nodes::procedural::CSymbol> portName,
			                           std::shared_ptr<ast::nodes::CNode> component)
				:   CNode(types::nodeType::PORT_ADDRESS),
				    m_portName(portName), m_component(component) {
                                    
                            if (!m_component.use_count()) {
                                m_component = std::make_shared<nodes::procedural::CSymbol>("self");
                            }
			}

			void CPortAddress::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CPortAddress::getPortName() const {
				return m_portName;
			}

			std::shared_ptr<ast::nodes::CNode> CPortAddress::getComponent() const {
				return m_component;
			}
		}
	}
}