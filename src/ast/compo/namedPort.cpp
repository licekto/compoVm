#include "ast/compo/namedPort.h"

namespace ast {

	namespace compo {

		CNamedPort::CNamedPort(std::shared_ptr<ast::procedural::CSymbol> name,
		                       bool atomicity,
		                       std::shared_ptr<ast::procedural::CSymbol> nameParam,
		                       bool collectivity)
			:   CNode(types::nodeType::PORT),
			    CPort(types::portType::NAMED, name, atomicity, collectivity),
			    m_nameParam(nameParam) {
		}

		void CNamedPort::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

		std::shared_ptr<ast::procedural::CSymbol> CNamedPort::getParamName() const {
			return m_nameParam;
		}
	}

}