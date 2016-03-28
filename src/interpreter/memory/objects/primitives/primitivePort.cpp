#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace primitives {

			CPrimitivePort::CPrimitivePort(const std::string& name, ptr(objects::CComponent) owner, ptr(objects::CComponent) connected)
				: CAbstractPrimitive(name, owner),
                                  m_connectedComponent(connected) {
			}
                        
                        CPrimitivePort::~CPrimitivePort() {
                        }
                        
                        void CPrimitivePort::setConnectedComponent(ptr(objects::CComponent) component) {
                            m_connectedComponent = component;
                        }

                        ptr(objects::CComponent) CPrimitivePort::getConnectedComponent() {
                            return m_connectedComponent;
                        }
                        
                    }
                    
		}
	}
}