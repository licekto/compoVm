#include "ast/nodes/compo/injectedPort.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CInjectedPort::CInjectedPort( std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                              bool atomic,
			                              std::shared_ptr<ast::nodes::procedural::CSymbol> injectedWith  )
				:   CNode(types::nodeType::INJECTED_PORT),
				    CPort(types::portType::INJECTED, name, atomic),
				    m_injectedWith(injectedWith) {
			}

			void CInjectedPort::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CInjectedPort::getInjectedWith() const {
				return m_injectedWith;
			}
		}
	}
}