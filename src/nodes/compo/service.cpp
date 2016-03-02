#include "nodes/compo/service.h"

namespace nodes {

	namespace compo {

		CService::CService(std::shared_ptr<nodes::compo::CServiceSignature> signature,
		                   std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::SERVICE),
			    CAbstractServConstr(signature, body) {
		}

		void CService::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << *m_body;
			outStr << "\t";
			outStr << "}" << std::endl;;
		}

	}

}