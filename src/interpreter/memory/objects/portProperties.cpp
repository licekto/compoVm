#include "interpreter/memory/objects/portProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                        
                        TPortProperties::TPortProperties(visibility v, type t, ptr(CComponent) port, ptr(CPrimitivePort) pPort)
                                : m_visibility(v), m_type(t), m_port(port), m_primitivePort(pPort) {
                        }

		}
	}
}
