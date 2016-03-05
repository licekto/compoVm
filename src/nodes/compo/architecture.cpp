#include "nodes/compo/architecture.h"
namespace nodes {

	namespace compo {

		CArchitecture::CArchitecture(const std::vector<std::shared_ptr<nodes::compo::CBind>>& architectureBody)
			: CNode(types::nodeType::ARCHITECTURE),
                          m_architectureBody(architectureBody){
		}

		void CArchitecture::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << "architecture {}";

			outStr << std::endl;
		}
                
                std::shared_ptr<nodes::compo::CBind> CArchitecture::getBodyNodeAt(unsigned int index) const {
                        std::shared_ptr<nodes::compo::CBind> node = nullptr;
			try {
				node = m_architectureBody.at(index);
			} catch (std::out_of_range ex) {
				// log error message
			}
			return node;
                }
	}
}