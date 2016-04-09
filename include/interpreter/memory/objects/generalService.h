#pragma once

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                        class CComponent;

			class CComponent;

			class CGeneralService {
			  private:
				ptr(CComponent) m_service;

				ptr(primitives::CPrimitiveService) m_primitiveService;

				bool m_primitive;

			  public:
				CGeneralService(ptr(CComponent) service = nullptr);

				CGeneralService(ptr(primitives::CPrimitiveService) primitiveService = nullptr);

				CGeneralService(ptr(CGeneralService) instance);

				ptr(CComponent) getService();

				ptr(primitives::CPrimitiveService) getPrimitiveService();

				bool isPrimitive() const;

				std::string getName() const;
                                
                                ptr(objects::CGeneralPort) invoke();
                                
                                ptr(objects::CGeneralPort) getDefaultPort();
			};
		}
	}
}
