#include "nodes/compo/service.h"

namespace nodes {

	namespace compo {

		CService::CService(   std::shared_ptr<nodes::procedural::CSymbol> name,
		                      const std::vector<std::shared_ptr<nodes::procedural::CSymbol>>& params,
		                      const std::vector<std::shared_ptr<nodes::CNode>>& body,
		                      const std::vector<std::shared_ptr<nodes::CNode>>& temporaries    )
			:   CNode(types::nodeType::SERVICE),
			    CAbstractServConstr(name, params, body),
			    m_temporaries(temporaries) {
		}

		size_t CService::getTemporariesSize() const {
			return m_temporaries.size();
		}

		std::shared_ptr<nodes::CNode> CService::getTemporaryAt(int index) const {
			std::shared_ptr<nodes::CNode> node = nullptr;
			try {
				node = m_temporaries.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
		}

		void CService::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << "service " << *m_name << " {" << std::endl;
			for (std::shared_ptr<nodes::CNode> node : m_body) {
				outStr << "\t\t";
				outStr << *node;
			}
			outStr << "\t";
			outStr << "}" << std::endl;;
		}

	}

}