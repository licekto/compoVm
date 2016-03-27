#pragma once

#include <string>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CPrimitiveCollectionPort : public CPrimitivePort, public std::enable_shared_from_this<CPrimitiveCollectionPort> {
			  private:
                                
                                std::vector<ptr(CComponent)> m_ports;
			  public:
                              
				CPrimitiveCollectionPort(const std::string& name = "", ptr(CComponent) owner = nullptr);
                                
                                size_t getPortsSize() const;
                                
                                void addPort(ptr(CComponent) port);
                                
                                ptr(CComponent) getPortAt(size_t index) const;
			};

		}
	}
}