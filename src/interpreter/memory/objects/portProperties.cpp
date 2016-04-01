#include "interpreter/memory/objects/portProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                    CPortProperties::CPortProperties(ptr(CComponent) port, portVisibility v, portType t, bool primitive)
                    : CAbstractPortProperties(v, t, primitive), m_port(port) {

                    }

                    CPortProperties::~CPortProperties() {
                    }

                    ptr(CComponent) CPortProperties::getPort() {
                        return m_port;
                    }
                    
		}
	}
}
