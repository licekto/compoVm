#include "nodes/compo/requirement.h"

namespace nodes {

	namespace compo {

		CRequirement::CRequirement(types::visibilityType type,
		                           const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports,
		                           bool universality)
			:   CNode(types::nodeType::REQUIREMENT),
			    CAbstractReqProv(type, ports, universality) {
		}

		void CRequirement::print(std::ostream& outstream) const {
			outstream << "provides" << std::endl;
		}

	}

}