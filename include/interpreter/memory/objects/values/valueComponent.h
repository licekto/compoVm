#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CValueComponent : public CComponent {
                                protected:
                                    
                                    type_values m_type;
                                    
				  public:

					CValueComponent(type_values type = type_values::INTEGER);

					virtual ~CValueComponent();

					void addDefaultPort(ptr(CGeneralPort) port);

					ptr(CGeneralPort) getDefaultPort();

					ptr(CGeneralPort) getPortByName(const std::string& name);
                                        
                                        type_values getType() const;

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