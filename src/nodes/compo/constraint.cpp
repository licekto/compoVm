#include "nodes/compo/constraint.h"

namespace nodes {

	namespace compo {

		CConstraint::CConstraint( std::shared_ptr<nodes::procedural::CSymbol> name,
		                          const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
		                          const std::vector<std::shared_ptr<nodes::CNode>>& body)
			:   CNode(types::nodeType::CONSTRAINT),
			    CAbstractServConstr(name, params, body) {
		}

	}
}