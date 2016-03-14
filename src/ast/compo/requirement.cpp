#include "ast/compo/requirement.h"

namespace ast {

	namespace compo {

		CRequirement::CRequirement(types::visibilityType type,
		                           const std::vector<std::shared_ptr<ast::compo::CPort>>& ports)
			:   CNode(types::nodeType::REQUIREMENT),
			    CAbstractReqProv(type, ports) {
		}

		void CRequirement::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

	}

}