#include "interpreter/memory/objects/stringComponent.h"

namespace interpreter {
    
    namespace memory {
        
        namespace objects {

            CStringComponent::CStringComponent(std::string value)
            : m_value(value) {
            }

            std::string CStringComponent::getValue() {
                return m_value;
            }

            void CStringComponent::setValue(std::string value) {
                m_value = value;
            }
            
        }
    }
}