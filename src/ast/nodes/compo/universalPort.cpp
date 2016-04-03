#include "ast/nodes/compo/universalPort.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CUniversalPort::CUniversalPort(std::shared_ptr<ast::nodes::procedural::CSymbol> name,
			                               bool atomicity,
			                               bool collectivity,
                                                       nodes::types::visibilityType visibility,
                                                       nodes::types::portRoleType role)
				:   CNode(types::nodeType::PORT),
				    CPort(types::portType::UNIVERSAL, name, atomicity, collectivity, visibility, role) {
			}

			void CUniversalPort::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}
		}
	}
}