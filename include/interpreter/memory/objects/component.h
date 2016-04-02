#pragma once

#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/abstractPortProperties.h"
#include "interpreter/memory/objects/primitives/primitivePortProperties.h"
#include "interpreter/config.h"
#include "primitives/primitivePortProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent {
			  private:

				std::vector<ptr(CAbstractPortProperties)> m_ports;

				std::vector<ptr(CGeneralService)> m_services;
                                
			  public:

                                virtual ~CComponent();
                              
				void addPort(ptr(CAbstractPortProperties) port);

				size_t getNumberOfPorts() const;

				ptr(CAbstractPortProperties) getPortAt(size_t index);

				ptr(primitives::CPrimitivePortProperties) getPrimitiveNamePort();

				ptr(CAbstractPortProperties) getPortByName(const std::string& name);
                                
                                ptr(CGeneralService) getServiceByName(const std::string& name);

				void addService(ptr(CGeneralService) service);
			};

		}
	}
}
