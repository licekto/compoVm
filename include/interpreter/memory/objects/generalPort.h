#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "types.h"
#include "generalService.h"
#include "exceptions/semantic/unsupportedFeatureException.h"
#include "exceptions/runtime/unknownPortTypeException.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;
                        class CGeneralService;
                        
			namespace primitives {
                                class CPrimitivePort;
			}

			class CGeneralPort : public std::enable_shared_from_this<CGeneralPort> {
			  protected:
				wptr(CComponent) m_port;

				wptr(primitives::CPrimitivePort) m_primitivePort;

				types::visibilityType m_visibility;

				types::roleType m_role;

				bool m_primitive;
                                
                                std::vector<wptr(CGeneralService)> m_connectedPrimitiveServices;

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
                                
                                void disconnectPortByName(const std::string& name);
                                
                                void connectPrimitiveService(ptr(CGeneralService) service);
                                
                                size_t getConnectedPrimitiveServicesNumber() const;
                                
                                ptr(CGeneralService) getPrimitiveServiceAt(size_t index);
                                
                                ptr(CGeneralPort) invokeByName(const std::string& selector, u64 index = 0);
                                
                                void delegateTo(ptr(CGeneralPort) port);
                                
                                ptr(CGeneralPort) getDelegatedPort();
                                
                                bool isCollection() const;
			};
		}
	}
}
