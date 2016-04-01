#include "interpreter/memory/objects/primitives/primitivePortProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace primitives {

                        CPrimitivePortProperties::CPrimitivePortProperties(ptr(CAbstractPrimitivePort) port, portVisibility v, portType t, bool primitive)
                        : CAbstractPortProperties(v, t, primitive), m_primitivePort(port) {

                        }

                        CPrimitivePortProperties::~CPrimitivePortProperties() {
                        }

                        ptr(CAbstractPrimitivePort) CPrimitivePortProperties::getPrimitivePort() {
                            return m_primitivePort;
                        }
                    
                    }
                    
		}
	}
}
