#include "ast/nodes/compo/namedPort.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CNamedPort::CNamedPort(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                       bool atomicity,
			                       bool collectivity,
			                       types::visibilityType visibility,
			                       types::roleType role,
			                       std::shared_ptr<ast::nodes::procedural::CSymbol> componentName)
				:   CNode(types::nodeType::NAMED_PORT),
				    CPort(types::portType::NAMED, name, atomicity, collectivity, visibility, role),
				    m_componentName(componentName) {
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