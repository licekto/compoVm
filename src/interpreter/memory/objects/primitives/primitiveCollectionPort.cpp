#include "interpreter/memory/objects/primitives/primitiveCollectionPort.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace primitives {
                    
                        CPrimitiveCollectionPort::CPrimitiveCollectionPort(const std::string& name, ptr(objects::CComponent) owner)
                        : CAbstractPrimitive(name, owner) {
                        }

                        CPrimitiveCollectionPort::~CPrimitiveCollectionPort() {
                        }

                        size_t CPrimitiveCollectionPort::getPortsSize() const {
                            return m_connectedPorts.size();
                        }

                        void CPrimitiveCollectionPort::connectComponent(ptr(objects::CComponent) port) {
                            m_connectedPorts.push_back(port);
                        }

                        ptr(objects::CComponent) CPrimitiveCollectionPort::getConnectedComponentAt(size_t index) const {
                            if (index < m_connectedPorts.size()) {
                                return m_connectedPorts.at(index);
                            }
                            //throw exception
                            return nullptr;
                        }
                    
                    }
                    
		}
	}
}