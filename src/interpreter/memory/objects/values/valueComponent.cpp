#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace values {

                        CValueComponent::CValueComponent() {
                        }
                        
                        CValueComponent::CValueComponent(std::shared_ptr<CValueComponent> instance)
                        : CComponent(instance) {
                        }

                        CValueComponent::~CValueComponent() {
                        }
                    }

		}
	}
}