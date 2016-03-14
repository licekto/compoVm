#include "ast/compo/portAddress.h"

namespace ast {

	namespace compo {

		CPortAddress::CPortAddress(std::shared_ptr<ast::procedural::CSymbol> portName,
		                           std::shared_ptr<ast::CNode> component)
			:   CNode(types::nodeType::PORT_ADDRESS),
			    m_portName(portName), m_component(component) {
		}

		void CPortAddress::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::procedural::CSymbol> CPortAddress::getPortName() const {
			return m_portName;
		}

		std::shared_ptr<ast::CNode> CPortAddress::getComponent() const {
			return m_component;
		}
	}

}