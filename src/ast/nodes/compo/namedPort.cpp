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
				    m_componentName(nameParam) {
			}

			void CNamedPort::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

			std::shared_ptr<ast::nodes::procedural::CSymbol> CNamedPort::getComponentName() const {
				return m_componentName;
			}
		}
	}
}