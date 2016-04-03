#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                    CGeneralPort::CGeneralPort(ptr(CComponent) port, portVisibility v, portType t)
                    : m_port(port), m_primitivePort(nullptr), m_visibility(v), m_type(t), m_primitive(false) {

                    }

                    CGeneralPort::CGeneralPort(ptr(primitives::CPrimitivePort) port, portVisibility v, portType t)
                    : m_port(nullptr), m_primitivePort(port), m_visibility(v), m_type(t), m_primitive(true) {

                    }
                    
                    CGeneralPort::CGeneralPort(ptr(CGeneralPort) instance)
                    : m_port(instance->m_port), m_primitivePort(instance->m_primitivePort),
                      m_visibility(instance->m_visibility), m_type(instance->m_type), m_primitive(instance->m_primitive) {

                    }

                    portVisibility CGeneralPort::getVisibility() const {
                        return m_visibility;
                    }
                    
                    portType CGeneralPort::getType() const {
                        return m_type;
                    }
                    
                    bool CGeneralPort::isPrimitive() const {
                        return m_primitive;
                    }

                    ptr(CComponent) CGeneralPort::getPort() {
                        return m_port;
                    }

                    ptr(primitives::CPrimitivePort) CGeneralPort::getPrimitivePort() {
                        return m_primitivePort;
                    }

                    std::string CGeneralPort::getName() const {
                        if (m_primitive) {
                            return m_primitivePort->getName();
                        }
                        else {
                            return m_port->getPortByName("name")->getPrimitivePort()->getName();
                        }
                    }

		}
	}
}
