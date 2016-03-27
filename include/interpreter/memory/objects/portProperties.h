#pragma once

#include <vector>

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    class CComponent;
                    class CPrimitivePort;
                    
                    enum visibility {
                        EXTERNAL,
                        INTERNAL
                    };
                    
                    enum type {
                        REQUIREMENT,
                        PROVISION
                    };
                    
                    struct TPortProperties {
                        visibility m_visibility;
                        type m_type;
                        ptr(CComponent) m_port;
                        ptr(CPrimitivePort) m_primitivePort;
                        
                        TPortProperties(visibility v = visibility::EXTERNAL, type t = type::PROVISION, ptr(CComponent) port = nullptr, ptr(CPrimitivePort) pPort = nullptr);
                    };

		}
	}
}
