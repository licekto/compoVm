#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/config.h"

#include "exceptions/runtime/portNotFoundException.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent {
			  protected:

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

                                size_t getNumberOfServices() const;
                                
                                ptr(CGeneralService) getServiceAt(size_t index);
                                
				ptr(CGeneralService) getServiceByName(const std::string& name);

				void addService(ptr(CGeneralService) service);

				ptr(CGeneralPort) getPortOfService(const std::string& serviceName);
                                
                                void removeServiceByName(const std::string& name);
                                
                                std::stringstream dump() const;
			};

		}
	}
}
