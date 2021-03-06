#pragma once

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/generalPort.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"
#include "exceptions/runtime/primitiveServiceNoPortException.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			class CGeneralService {
			  private:
				wptr(CComponent) m_service;

				wptr(primitives::CPrimitiveService) m_primitiveService;

				bool m_primitive;

				ptr(CGeneralService) m_specialized;

			  public:
				CGeneralService(ptr(CComponent) service = nullptr, ptr(CGeneralService) specialized = nullptr);

				CGeneralService(ptr(primitives::CPrimitiveService) primitiveService = nullptr);

				ptr(CComponent) getService();

				ptr(primitives::CPrimitiveService) getPrimitiveService();

				bool isPrimitive() const;

				std::string getName() const;

				ptr(objects::CGeneralPort) invoke();

				ptr(objects::CGeneralPort) getDefaultPort();

				ptr(CGeneralService) getSpecialized();
			};
		}
	}
}
