#include "interpreter/memory/objects/primitiveCollectionPort.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    CPrimitiveCollectionPort::CPrimitiveCollectionPort(const std::string& name, ptr(CComponent) owner)
                    : CPrimitivePort(name, owner) {
                    }

                    size_t CPrimitiveCollectionPort::getPortsSize() const {
                        return m_ports.size();
                    }

                    void CPrimitiveCollectionPort::addPort(std::shared_ptr<CComponent> port) {
                        m_ports.push_back(port);
                    }

                    std::shared_ptr<CComponent> CPrimitiveCollectionPort::getPortAt(size_t index) const {
                        if (index < m_ports.size()) {
                            return m_ports.at(index);
                        }
                        //throw exception
                        return nullptr;
                    }
                    
		}
	}
}