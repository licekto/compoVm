#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {
                            
                                CAbstractPrimitivePort::CAbstractPrimitivePort(const std::string& name, std::shared_ptr<objects::CComponent> owner)
					: CAbstractPrimitive(name, owner) {
                                }

                                CAbstractPrimitivePort::~CAbstractPrimitivePort() {
                                }

			}

		}
	}
}