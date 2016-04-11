#include "interpreter/memory/objects/values/stringComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CStringComponent::CStringComponent(const std::string& value)
					: CValueComponent(), m_value(value) {
				}

				CStringComponent::CStringComponent(ptr(CStringComponent) instance)
					: CValueComponent(), m_value(instance->m_value) {
				}

				CStringComponent::~CStringComponent() {

				}

				std::string CStringComponent::getValue() {
					return m_value;
				}

				void CStringComponent::setValue(const std::string& value) {
					m_value = value;
				}

			}
		}
	}
}