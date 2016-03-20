#include "ast/nodes/compo/provision.h"

namespace ast {

    namespace nodes {
    
	namespace compo {

		CProvision::CProvision(types::visibilityType type,
		                       const std::vector<std::shared_ptr<ast::nodes::compo::CPort>>& ports)
			:   CNode(types::nodeType::PROVISION),
			    CAbstractReqProv(type, ports) {
		}

		void CProvision::accept(visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

	}
    }
}