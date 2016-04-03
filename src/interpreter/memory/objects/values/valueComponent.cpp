#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace values {

                        CValueComponent::CValueComponent() {
                            ptr(primitives::CPrimitivePort) primitivePort = new_ptr(primitives::CPrimitivePort)("default", this->shared_from_this());
                            
                            ptr(CGeneralPort) generalPort = new_ptr(CGeneralPort)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
                            
                            m_ports.push_back(generalPort);
                        }
                        
                        CValueComponent::CValueComponent(ptr(CValueComponent) instance)
                        : CComponent(instance) {
                        }

                        CValueComponent::~CValueComponent() {
                        }

                        ptr(CGeneralPort) CValueComponent::getDefaultPort() {
                            return m_ports.at(0);
                        }

                    }

		}
	}
}