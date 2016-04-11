#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CValueComponent : public CComponent {
				  public:

					CValueComponent();

					virtual ~CValueComponent();

					void addDefaultPort(ptr(CGeneralPort) port);

					ptr(CGeneralPort) getDefaultPort();

					ptr(CGeneralPort) getPortByName(const std::string& name);

					void addPort(ptr(CGeneralPort) port) = delete;

					size_t getNumberOfPorts() const = delete;

					ptr(CGeneralPort) getPortAt(size_t index) = delete;

					ptr(CComponent) getServiceByName(const std::string& name) = delete;

					ptr(primitives::CPrimitiveService) getPrimitiveServiceByName(const std::string& name) = delete;

					void addService(ptr(CComponent) service) = delete;

					void addPrimitiveService(ptr(primitives::CPrimitiveService) service) = delete;
				};
			}
		}
	}
}