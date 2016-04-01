#include "interpreter/memory/objects/unsignedIntComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                        CUnsignedIntComponent::~CUnsignedIntComponent() {
                        }

			CUnsignedIntComponent::CUnsignedIntComponent(u64 value)
				: m_value(value) {
			}

			u64 CUnsignedIntComponent::getValue() {
				return m_value;
			}

			void CUnsignedIntComponent::setValue(u64 value) {
				m_value = value;
			}

		}
	}
}