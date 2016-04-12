#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "types.h"
#include "generalService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;
                        class CGeneralService;
                        
			namespace primitives {
                                class CPrimitivePort;
			}

			class CGeneralPort {
			  protected:
				ptr(CComponent) m_port;

				ptr(primitives::CPrimitivePort) m_primitivePort;

				types::visibilityType m_visibility;

				types::roleType m_type;

				bool m_primitive;
                                
                                std::vector<ptr(CGeneralService)> m_connectedPrimitiveServices;

			  public:
				CGeneralPort(ptr(CComponent) port,
				             types::visibilityType v = types::visibilityType::EXTERNAL,
				             types::roleType t = types::roleType::PROVIDES);

				CGeneralPort(ptr(primitives::CPrimitivePort) port,
				             types::visibilityType v = types::visibilityType::EXTERNAL,
				             types::roleType t = types::roleType::PROVIDES);

				types::visibilityType getVisibility() const;

				types::roleType getRole() const;

				bool isPrimitive() const;

				ptr(CComponent) getPort();

				ptr(primitives::CPrimitivePort) getPrimitivePort();

				std::string getName() const;

				ptr(CComponent) getOwner();

				void setOwner(ptr(CComponent) owner);

				size_t getConnectedPortsNumber() const;

				ptr(objects::CGeneralPort) getConnectedPortAt(size_t index);

				void connectPort(ptr(objects::CGeneralPort) port);

				void disconnectPortAt(size_t index);
                                
                                void connectPrimitiveService(ptr(CGeneralService) service);
                                
                                size_t getConnectedPrimitiveServicesNumber() const;
                                
                                ptr(CGeneralService) getPrimitiveServiceAt(size_t index);
			};
		}
	}
}
