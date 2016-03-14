#include "ast/compo/constraint.h"

namespace ast {

	namespace compo {

		CConstraint::CConstraint(std::shared_ptr<ast::compo::CServiceSignature> signature,
		                         std::shared_ptr<ast::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::CONSTRAINT),
			    CAbstractServConstr(signature, body) {
		}

		void CConstraint::print(std::ostream& outstream) const {
			outstream << "constraint()" << std::endl;
		}

	}
}