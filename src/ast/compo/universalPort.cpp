#include "ast/compo/universalPort.h"

namespace ast {

	namespace compo {

		CUniversalPort::CUniversalPort(std::shared_ptr<ast::procedural::CSymbol> name,
		                               bool atomicity,
		                               bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::UNIVERSAL, name, atomicity, collectivity) {
		}

		void CUniversalPort::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }
	}

}