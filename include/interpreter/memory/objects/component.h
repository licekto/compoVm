#pragma once

#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/portProperties.h"
#include "interpreter/memory/objects/primitives/primitivePortProperties.h"
#include "interpreter/config.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {
				class CPrimitiveService;
			}

			class CComponent {
			  private:

				std::vector<ptr(CAbstractPortProperties)> m_ports;

				std::vector<ptr(CComponent)> m_services;

				std::vector<ptr(primitives::CPrimitiveService)> m_primitiveServices;
                                
			  public:

                                virtual ~CComponent();
                              
				void addPort(ptr(CAbstractPortProperties) port);

				size_t getNumberOfPorts() const;

				ptr(CAbstractPortProperties) getPortAt(size_t index);

				ptr(primitives::CPrimitivePortProperties) getPrimitiveNamePort();

				ptr(CAbstractPortProperties) getPortByName(const std::string& name);
                                
                                ptr(CComponent) getServiceByName(const std::string& name);
                                
                                ptr(primitives::CPrimitiveService) getPrimitiveServiceByName(const std::string& name);

				void addService(ptr(CComponent) service);

				void addPrimitiveService(ptr(primitives::CPrimitiveService) service);
			};

		}
	}
}
