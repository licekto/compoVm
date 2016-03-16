#include "ast/compo/injectedPort.h"

namespace ast {

	namespace compo {

		CInjectedPort::CInjectedPort( std::shared_ptr<ast::procedural::CSymbol> name,
		                              bool atomic,
		                              std::shared_ptr<ast::procedural::CSymbol> injectedWith  )
			:   CNode(types::nodeType::INJECTED_PORT),
			    CPort(ast::types::portType::INJECTED, name, atomic),
			    m_injectedWith(injectedWith) {
		}

		void CInjectedPort::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::procedural::CSymbol> CInjectedPort::getInjectedWith() const {
                    return m_injectedWith;
		}
	}

}