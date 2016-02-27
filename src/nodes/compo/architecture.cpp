#include "nodes/compo/architecture.h"
namespace nodes {

	namespace compo {

		CArchitecture::CArchitecture()
			: CNode(types::nodeType::ARCHITECTURE) {
		}

		void CArchitecture::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << "architecture {}";

			outStr << std::endl;
		}
	}
}