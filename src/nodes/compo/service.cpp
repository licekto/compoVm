#include "nodes/compo/service.h"

namespace nodes {

	namespace compo {

		CService::CService(std::shared_ptr<nodes::procedural::CSymbol> name,
                                   const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
                                   std::shared_ptr<nodes::procedural::CCompoundBody> body)
			:   CNode(types::nodeType::SERVICE),
			    CAbstractServConstr(name, params, body) {
		}

		void CService::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << "service " << *m_name << " {" << std::endl;
			outStr << *m_body;
			outStr << "\t";
			outStr << "}" << std::endl;;
		}

	}

}