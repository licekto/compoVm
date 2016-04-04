#include "interpreter/memory/objects/values/boolComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CBoolComponent::CBoolComponent(bool value)
					: m_value(value) {
				}

				CBoolComponent::CBoolComponent(ptr(CBoolComponent) instance)
					: CValueComponent(instance), m_value(instance->m_value) {
				}

				CBoolComponent::~CBoolComponent() {
				}

				bool CBoolComponent::getValue() {
					return m_value;
				}

				void CBoolComponent::setValue(bool value) {
					m_value = value;
				}

			}
		}
	}
}