#include "nodes/compo/constraint.h"

namespace nodes {

	namespace compo {

		CConstraint::CConstraint(std::shared_ptr<nodes::compo::CServiceSignature> signature,
		                         std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::CONSTRAINT),
			    CAbstractServConstr(signature, body) {
		}

		void CConstraint::print(std::ostream& outstream) const {
			outstream << "constraint()" << std::endl;
		}

	}
}