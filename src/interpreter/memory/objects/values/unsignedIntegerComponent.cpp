#include "interpreter/memory/objects/values/unsignedIntegerComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CUnsignedIntegerComponent::CUnsignedIntegerComponent(u64 value)
					: m_value(value) {
				}

				CUnsignedIntegerComponent::CUnsignedIntegerComponent(ptr(CUnsignedIntegerComponent) instance)
					: CValueComponent(), m_value(instance->m_value) {
				}

				CUnsignedIntegerComponent::~CUnsignedIntegerComponent() {

				}

				u64 CUnsignedIntegerComponent::getValue() {
					return m_value;
				}

				void CUnsignedIntegerComponent::setValue(u64 value) {
					m_value = value;
				}

			}
		}
	}
}