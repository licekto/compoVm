#include "ast/nodes/compo/injectedPort.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		CInjectedPort::CInjectedPort( std::shared_ptr<ast::nodes::procedural::CSymbol> name,
		                              bool atomic,
		                              std::shared_ptr<ast::nodes::procedural::CSymbol> injectedWith  )
			:   CNode(types::nodeType::INJECTED_PORT),
			    CPort(ast::nodes::types::portType::INJECTED, name, atomic),
			    m_injectedWith(injectedWith) {
		}

		void CInjectedPort::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CInjectedPort::getInjectedWith() const {
			return m_injectedWith;
		}
	}
    }
}