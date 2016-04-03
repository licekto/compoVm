#include "ast/nodes/compo/requirement.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CRequirement::CRequirement(types::visibilityType type,
			                           const std::vector<std::shared_ptr<ast::nodes::compo::CPort>>& ports)
				:   CNode(types::nodeType::REQUIREMENT),
				    CAbstractReqProv(type, ports) {
                            
                            for(std::shared_ptr<ast::nodes::compo::CPort> port : m_ports) {
                                port->setVisibility(type);
                                port->setRole(nodes::types::portRoleType::REQUIRES);
                            }
			}

			void CRequirement::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

		}
	}
}