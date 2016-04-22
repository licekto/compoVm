#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/values/stringComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CGeneralService::CGeneralService(ptr(CComponent) service, ptr(CGeneralService) specialized)
				: m_service(wptr(CComponent)(service)),
				  m_primitive(false),
				  m_specialized(specialized) {
			}

			CGeneralService::CGeneralService(ptr(primitives::CPrimitiveService) primitiveService)
				: m_primitiveService(wptr(primitives::CPrimitiveService)(primitiveService)),
				  m_primitive(true) {
			}

			ptr(CComponent) CGeneralService::getService() {
				return m_service.lock();
			}

			ptr(primitives::CPrimitiveService) CGeneralService::getPrimitiveService() {
				return m_primitiveService.lock();
			}

			bool CGeneralService::isPrimitive() const {
				return m_primitive;
			}

			std::string CGeneralService::getName() const {
				if (m_primitive) {
					return m_primitiveService.lock()->getName();
				} else {
					return cast(values::CStringComponent)
					       (m_service.lock()->getPortByName("serviceSign")->getConnectedPortAt(0)
					        ->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue();
				}
			}

			ptr(objects::CGeneralPort) CGeneralService::invoke() {
				if (m_primitive) {
					return m_primitiveService.lock()->invoke();
				} else {
					return m_service.lock()->getServiceByName("execute")->invoke();
				}
			}

			ptr(objects::CGeneralPort) CGeneralService::getDefaultPort() {
				if (m_primitive) {
					throw exceptions::runtime::CPrimitiveServiceNoPortException();
				}
				return m_service.lock()->getPortByName("default");
			}

			ptr(CGeneralService) CGeneralService::getSpecialized() {
				return m_specialized;
			}

		}
	}
}
