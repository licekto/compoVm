#pragma once

#include <string>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    class CComponent;
                    
                    namespace primitives {

			class CPrimitiveCollectionPort : public CAbstractPrimitive {
			  private:
                                
                                std::vector<ptr(objects::CComponent)> m_connectedPorts;
                                
			  public:
                              
				CPrimitiveCollectionPort(const std::string& name = "", ptr(objects::CComponent) owner = nullptr);
                                
                                virtual ~CPrimitiveCollectionPort();
                                
                                size_t getPortsSize() const;
                                
                                void connectComponent(ptr(objects::CComponent) port);
                                
                                ptr(objects::CComponent) getConnectedComponentAt(size_t index) const;
                                
                                void setConnectedComponent(ptr(objects::CComponent) component) = delete;
                                
                                ptr(objects::CComponent) getConnectedComponent() = delete;
			};
                        
                    }

		}
	}
}