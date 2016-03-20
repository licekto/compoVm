#include "ast/nodes/compo/constraint.h"

namespace ast {
    
    namespace nodes {

	namespace compo {

		CConstraint::CConstraint(std::shared_ptr<ast::nodes::compo::CServiceSignature> signature,
		                         std::shared_ptr<ast::nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::CONSTRAINT),
			    CAbstractServConstr(signature, body) {
		}

		void CConstraint::accept(ast::visitors::CAbstractVisitor* visitor) {
			visitor->visit(this);
		}

	}
    }
}