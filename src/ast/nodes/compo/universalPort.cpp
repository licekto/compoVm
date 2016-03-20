#include "ast/nodes/compo/universalPort.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CUniversalPort::CUniversalPort(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
		                               bool atomicity,
		                               bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::UNIVERSAL, name, atomicity, collectivity) {
		}

		void CUniversalPort::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}
	}
    }
}