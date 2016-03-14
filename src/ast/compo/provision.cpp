#include "ast/compo/provision.h"

namespace ast {

	namespace compo {

		CProvision::CProvision(types::visibilityType type,
		                       const std::vector<std::shared_ptr<ast::compo::CPort>>& ports)
			:   CNode(types::nodeType::PROVISION),
			    CAbstractReqProv(type, ports) {
		}

		void CProvision::print(std::ostream& outstream) const {
			outstream << "provides" << std::endl;
		}

	}

}