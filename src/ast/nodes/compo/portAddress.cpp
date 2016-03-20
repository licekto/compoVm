#include "ast/nodes/compo/portAddress.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CPortAddress::CPortAddress(std::shared_ptr<ast::nodes::procedural::CSymbol> portName,
		                           std::shared_ptr<ast::nodes::CNode> component)
			:   CNode(types::nodeType::PORT_ADDRESS),
			    m_portName(portName), m_component(component) {
		}

		void CPortAddress::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
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