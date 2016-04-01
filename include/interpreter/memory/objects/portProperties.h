#pragma once

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/abstractPortProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;
                        
                        class CPortProperties : public CAbstractPortProperties {
                        private:
                            ptr(CComponent) m_port;
                            
                        public:
                            CPortProperties(ptr(CComponent) port = nullptr,
                                            portVisibility v = portVisibility::EXTERNAL,
                                            portType t = portType::PROVISION,
                                            bool primitive = false);
                            
                            virtual ~CPortProperties();
                            
                            ptr(CComponent) getPort();
                        };
		}
	}
}
