#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

#include "logger/logger.h"
#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/config.h"

#include "exceptions/runtime/portNotFoundException.h"
#include "exceptions/runtime/serviceNotFoundException.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent {
			  protected:

				ptr(CComponent) m_parent;

				ptr(CComponent) m_child;

				std::vector<ptr(CGeneralPort)> m_ports;

				std::vector<ptr(CGeneralService)> m_services;

			  public:

				CComponent();

				virtual ~CComponent();

				size_t getNumberOfPorts() const;

				void addPort(ptr(CGeneralPort) port);

				ptr(CGeneralPort) getSelfPortByName(const std::string& name);

				ptr(CGeneralPort) getPortByName(const std::string& name);

				size_t getNumberOfInheritedServices() const;

				size_t getNumberOfSelfServices() const;

				size_t getNumberOfAllServices() const;

				void connectAllSelfServicesTo(ptr(CGeneralPort) port);

				void connectAllParentServicesTo(ptr(CGeneralPort) port);

				void connectAllServicesTo(ptr(CGeneralPort) port);

				ptr(CGeneralService) getSelfServiceByName(const std::string& name);

				ptr(CGeneralService) getServiceByName(const std::string& name);

				void addService(ptr(CGeneralService) service);

				ptr(CGeneralPort) getPortOfService(const std::string& serviceName);

				void removeServiceByName(const std::string& name);

				ptr(CComponent) getParent();

				ptr(CComponent) getTopParent();

				void setParent(ptr(CComponent) parent);

				ptr(CComponent) getChild();

				ptr(CComponent) getBottomChild();

				void setChild(ptr(CComponent) child);

				std::stringstream dump() const;
			};

		}
	}
}
