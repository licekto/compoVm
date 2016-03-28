#include "interpreter/memory/objects/portProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                        
                        TPortProperties::TPortProperties(portVisibility v, portType t, ptr(CComponent) port, ptr(primitives::CAbstractPrimitive) pPort)
                                : m_visibility(v), m_type(t), m_port(port), m_primitivePort(pPort) {
                        }

		}
	}
}
