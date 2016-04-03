#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/types.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                        
                        class CComponent;

                        namespace primitives {
                            class CPrimitivePort;
                        }
                    
                        class CGeneralPort {
                        protected:
                            ptr(CComponent) m_port;
                            
                            ptr(primitives::CPrimitivePort) m_primitivePort;
                            
                            portVisibility m_visibility;
                            
                            portType m_type;
                            
                            bool m_primitive;
                            
                        public:
                            CGeneralPort(ptr(CComponent) port,
                                         portVisibility v = portVisibility::EXTERNAL,
                                         portType t = portType::PROVISION);

                            CGeneralPort(ptr(primitives::CPrimitivePort) port,
                                         portVisibility v = portVisibility::EXTERNAL,
                                         portType t = portType::PROVISION);
                            
                            CGeneralPort(ptr(CGeneralPort) instance);
                            
                            portVisibility getVisibility() const;
                            
                            portType getType() const;
                            
                            bool isPrimitive() const;
                            
                            ptr(CComponent) getPort();
                            
                            ptr(primitives::CPrimitivePort) getPrimitivePort();
                            
                            std::string getName() const;
                        };
		}
	}
}
