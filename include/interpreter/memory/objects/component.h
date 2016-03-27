#pragma once

#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/portProperties.h"
#include "interpreter/memory/objects/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                        
			class CComponent {
			  private:

                                std::vector<ptr(TPortProperties)> m_ports;
                                
                                std::vector<ptr(CComponent)> m_services;

			  public:

				void addPort(ptr(TPortProperties));
                                
                                size_t getNumberOfPorts() const;
                                
                                ptr(TPortProperties) getPortAt(size_t index);
                                
                                ptr(CPrimitivePort) getPrimitivePortByName(const std::string& name);
                                
				void addService(ptr(CComponent) service);
			};

		}
	}
}
