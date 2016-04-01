#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/abstractPortProperties.h"
#include "abstractPrimitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                    namespace primitives {
                        
                        class CPrimitivePortProperties : public CAbstractPortProperties {
                        private:
                            ptr(CAbstractPrimitivePort) m_primitivePort;
                            
                        public:
                            CPrimitivePortProperties(ptr(CAbstractPrimitivePort) port = nullptr,
                                                     portVisibility v = portVisibility::EXTERNAL,
                                                     portType t = portType::PROVISION,
                                                     bool primitive = false);
                            
                            virtual ~CPrimitivePortProperties();
                            
                            ptr(CAbstractPrimitivePort) getPrimitivePort();
                        };
                    }
		}
	}
}
