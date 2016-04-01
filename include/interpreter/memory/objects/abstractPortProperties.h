#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/types.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                        
                        class CAbstractPortProperties {
                        protected:
                            portVisibility m_visibility;
                            portType m_type;
                            bool m_primitive;
                            
                        public:
                            CAbstractPortProperties(portVisibility v = portVisibility::EXTERNAL,
                                            portType t = portType::PROVISION,
                                            bool primitive = false);
                            
                            virtual ~CAbstractPortProperties() = 0;
                            
                            portVisibility getVisibility() const;
                            
                            portType getType() const;
                            
                            bool isPrimitive() const;
                        };
		}
	}
}
