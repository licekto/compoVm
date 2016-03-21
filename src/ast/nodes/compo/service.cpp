#include "ast/nodes/compo/service.h"

namespace ast {

	namespace nodes {

		namespace compo {

			CService::CService(std::shared_ptr<ast::nodes::compo::CServiceSignature> signature,
			                   std::shared_ptr<ast::nodes::procedural::CCompoundBody> body)
				:   CNode(types::nodeType::SERVICE),
				    CAbstractServConstr(signature, body) {
			}

			void CService::accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) {
				visitor->visit(shared_from_this());
			}

		}
	}
}