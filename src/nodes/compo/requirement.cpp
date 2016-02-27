#include "nodes/compo/requirement.h"

namespace nodes {

	namespace compo {

		CRequirement::CRequirement(   types::visibilityType type,
		                              const std::vector<std::shared_ptr<nodes::compo::CPort>>& ports)
			:   CNode(types::nodeType::REQUIREMENT),
			    CAbstractReqProv(type, ports) {
		}
	}

}