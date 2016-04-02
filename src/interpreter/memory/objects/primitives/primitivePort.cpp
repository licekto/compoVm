#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {
                            
                                CPrimitivePort::CPrimitivePort(const std::string& name, std::shared_ptr<objects::CComponent> owner, ptr(objects::CComponent) connected)
					: CAbstractPrimitivePort(name, owner),
					  m_connectedComponent(connected) {
				}

				CPrimitivePort::~CPrimitivePort() {
				}

				void CPrimitivePort::setConnectedComponent(ptr(objects::CComponent) component) {
					m_connectedComponent = component;
				}

				ptr(objects::CComponent) CPrimitivePort::getConnectedComponent() {
					return m_connectedComponent;
                                }

                                void CPrimitivePort::setConnectedService(std::shared_ptr<objects::CGeneralService> service) {
                                    m_connectedServices.push_back(service);
                                }

                                size_t CPrimitivePort::getConnectedServicesNumber() const {
                                    return m_connectedServices.size();
                                }

                                std::shared_ptr<objects::CGeneralService> CPrimitivePort::getConnectedServiceAt(size_t index) {
                                    if (index < m_connectedServices.size()) {
                                        return m_connectedServices.at(index);
                                    }
                                    // throw
                                    return nullptr;
                                }

			}

		}
	}
}