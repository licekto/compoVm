#include "nodes/compo/provision.h"

namespace nodes {

	namespace compo {

		CProvision::CProvision(types::visibilityType type,
		                       const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports)
			:   CNode(types::nodeType::PROVISION),
			    CAbstractReqProv(type, ports) {
		}

		void CProvision::print(std::ostream& outstream) const {
			outstream << "provides" << std::endl;
		}

	}

}