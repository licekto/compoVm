#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CPrimitiveService::CPrimitiveService(const std::string& name,
				                                     ptr(objects::CComponent) context,
				                                     std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback)
					: CAbstractPrimitive(name, context),
					  m_callback(callback) {
				}

				CPrimitiveService::CPrimitiveService(ptr(CPrimitiveService) instance)
					: CAbstractPrimitive(instance),
					  m_callback(instance->m_callback) {
				}

				CPrimitiveService::~CPrimitiveService() {
				}

				ptr(CComponent) CPrimitiveService::getContext() {
					return m_owner.lock();
				}

				void CPrimitiveService::setContext(ptr(CComponent) context) {
					m_owner = wptr(CComponent)(context);
				}

				ptr(objects::CGeneralPort) CPrimitiveService::invoke() {
					return m_callback(m_owner.lock());
				}

				void CPrimitiveService::setCallback(std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback) {
					m_callback = callback;
				}

				std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> CPrimitiveService::getCallback() const {
					return m_callback;
				}

			}

		}
	}
}