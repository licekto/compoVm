#include "interpreter/memory/objects/abstractPortProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                    CAbstractPortProperties::CAbstractPortProperties(portVisibility v, portType t, bool primitive)
                    : m_visibility(v), m_type(t), m_primitive(primitive) {

                    }

                    CAbstractPortProperties::~CAbstractPortProperties() {
                    }

                    portVisibility CAbstractPortProperties::getVisibility() const {
                        return m_visibility;
                    }
                    
                    portType CAbstractPortProperties::getType() const {
                        return m_type;
                    }
                    
                    bool CAbstractPortProperties::isPrimitive() const {
                        return m_primitive;
                    }

		}
	}
}
