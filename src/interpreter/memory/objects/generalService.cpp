#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"

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
                            
                            CGeneralService::CGeneralService(ptr(CGeneralService) instance)
                            : m_service(instance->m_service), m_primitiveService(instance->m_primitiveService),
                              m_primitive(instance->m_primitive){   
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

                            std::string CGeneralService::getName() const {
                                if (m_primitive) {
                                    return m_primitiveService->getName();
                                }
                                else {
                                    //return m_service->getPortByName("serviceSign")->getPrimitivePort()->getConnectedPortAt(0)
                                    return "";
                                }
                            }

		}
	}
}
