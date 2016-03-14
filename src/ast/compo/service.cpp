#include "ast/compo/service.h"

namespace ast {

	namespace compo {

		CService::CService(std::shared_ptr<ast::compo::CServiceSignature> signature,
		                   std::shared_ptr<ast::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::SERVICE),
			    CAbstractServConstr(signature, body) {
		}

		void CService::accept(ast::visitors::CAbstractStringVisitor* visitor) {
                    visitor->visit(this);
                }

	}

}