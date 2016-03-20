#include "ast/nodes/compo/namedPort.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CNamedPort::CNamedPort(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
		                       bool atomicity,
		                       std::shared_ptr<ast::nodes::procedural::CSymbol> nameParam,
		                       bool collectivity)
			:   CNode(types::nodeType::NAMED_PORT),
			    CPort(types::portType::NAMED, name, atomicity, collectivity),
			    m_nameParam(nameParam) {
		}

		void CNamedPort::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

		std::shared_ptr<ast::nodes::procedural::CSymbol> CNamedPort::getParamName() const {
			return m_nameParam;
		}
	}
    }
}