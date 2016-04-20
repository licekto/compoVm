#include "interpreter/memory/objects/values/signedIntegerComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CSignedIntegerComponent::CSignedIntegerComponent(i64 value)
					: CValueComponent(type_values::INTEGER), m_value(value) {
				}

				CSignedIntegerComponent::CSignedIntegerComponent(ptr(CSignedIntegerComponent) instance)
					: CValueComponent(type_values::INTEGER), m_value(instance->m_value) {
				}

				CSignedIntegerComponent::~CSignedIntegerComponent() {

				}

				i64 CSignedIntegerComponent::getValue() {
					return m_value;
				}

				void CSignedIntegerComponent::setValue(i64 value) {
					m_value = value;
				}

			}
		}
	}
}