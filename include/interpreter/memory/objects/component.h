#pragma once

#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/config.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent {
			  private:

				std::vector<ptr(CGeneralPort)> m_ports;

				std::vector<ptr(CGeneralService)> m_services;
                                
			  public:

                                CComponent();
                              
                                CComponent(ptr(CComponent) instance);
                              
                                virtual ~CComponent();
                              
				void addPort(ptr(CGeneralPort) port);

				size_t getNumberOfPorts() const;

				ptr(CGeneralPort) getPortAt(size_t index);

				ptr(CGeneralPort) getPortByName(const std::string& name);
                                
                                ptr(CGeneralService) getServiceByName(const std::string& name);

				void addService(ptr(CGeneralService) service);
			};

		}
	}
}
