#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    class CComponent;
                    class CPrimitivePort;
                    
                    enum portVisibility {
                        EXTERNAL,
                        INTERNAL
                    };
                    
                    enum portType {
                        REQUIREMENT,
                        PROVISION
                    };
                    
                    struct TPortProperties {
                        portVisibility m_visibility;
                        portType m_type;
                        ptr(CComponent) m_port;
                        ptr(primitives::CAbstractPrimitive) m_primitivePort;
                        
                        TPortProperties(portVisibility v = portVisibility::EXTERNAL, portType t = portType::PROVISION, ptr(CComponent) port = nullptr, ptr(primitives::CAbstractPrimitive) pPort = nullptr);
                    };

		}
	}
}
