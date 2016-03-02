#include "nodes/compo/constraint.h"

namespace nodes {

	namespace compo {

		CConstraint::CConstraint(std::shared_ptr<nodes::procedural::CSymbol> name,
                                         const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
                                         std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::CONSTRAINT),
			    CAbstractServConstr(name, params, body) {
		}
                
                void CConstraint::print(std::ostream& outstream) const {
                    outstream << "constraint()" << std::endl;
		}

	}
}