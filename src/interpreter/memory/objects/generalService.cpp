#include "interpreter/memory/objects/generalService.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                            
                            CGeneralService::CGeneralService(ptr(CComponent) service)
                            : m_service(service),
                              m_primitiveService(nullptr),
                              m_primitive(false) {
                            }
                            
                            CGeneralService::CGeneralService(ptr(primitives::CPrimitiveService) primitiveService)
                            : m_service(nullptr),
                              m_primitiveService(primitiveService),
                              m_primitive(true) {
                            }
                            
                            ptr(CComponent) CGeneralService::getService() {
                                return m_service;
                            }
                            
                            ptr(primitives::CPrimitiveService) CGeneralService::getPrimitiveService() {
                                return m_primitiveService;
                            }
                            
                            bool CGeneralService::isPrimitive() const {
                                return m_primitive;
                            }
		}
	}
}
