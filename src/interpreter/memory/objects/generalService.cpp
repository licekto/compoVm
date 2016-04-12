#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/values/stringComponent.h"

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

			std::string CGeneralService::getName() const {
				if (m_primitive) {
					return m_primitiveService->getName();
				} else {
					return cast(values::CStringComponent)
					       (m_service->getPortByName("serviceSign")->getConnectedPortAt(0)
					        ->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

			ptr(objects::CGeneralPort) CGeneralService::invoke() {
				if (m_primitive) {
					return m_primitiveService->invoke();
				} else {
					TRACE(ERROR, "Not implemented yet");
					return nullptr;
				}
			}

			ptr(objects::CGeneralPort) CGeneralService::getDefaultPort() {
                                if (m_primitive) {
                                    // throw
                                    TRACE(ERROR, "Primitive service doesn't have primitive port!");
                                }
				return m_service->getPortByName("default");
			}

		}
	}
}
