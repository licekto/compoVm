#include "nodes/compo/architecture.h"
namespace nodes {

	namespace compo {

		CArchitecture::CArchitecture()
			: CNode(types::nodeType::ARCHITECTURE) {
		}

		CArchitecture::CArchitecture(const CArchitecture& other)
			: CNode(other) {
		}

		CArchitecture::CArchitecture(CArchitecture&& other) noexcept
			: CNode(std::move(other)) {
		}

		CArchitecture& CArchitecture::operator =(const CArchitecture& other) {
			if (&other != this) {
			}

			return *this;
		}

		CArchitecture& CArchitecture::operator =(CArchitecture&& other) noexcept {
			if (&other != this) {
			}
			return *this;
		}

		CNode * CArchitecture::clone() const {
			return new CArchitecture(*this);
		}

		CArchitecture::~CArchitecture() {}

		void CArchitecture::print(std::ostream& outStr) const {
			outStr << "\t";
			outStr << "architecture {}";

			outStr << std::endl;
		}
	}
}