#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CPrimitivePort::CPrimitivePort(const std::string& name, std::shared_ptr<objects::CComponent> owner)
					: CAbstractPrimitive(name, owner) {
				}

				CPrimitivePort::CPrimitivePort(ptr(CPrimitivePort) instance)
					: CAbstractPrimitive(instance) {
					for (ptr(CGeneralPort) port : instance->m_connectedPorts) {
						this->m_connectedPorts.push_back(new_ptr(CGeneralPort)(port));
					}
					for (ptr(CGeneralService) service : instance->m_connectedServices) {
						this->m_connectedServices.push_back(new_ptr(CGeneralService)(service));
					}
				}

				CPrimitivePort::~CPrimitivePort() {
				}

				size_t CPrimitivePort::getConnectedPortsNumber() const {
					return m_connectedPorts.size();
				}

				void CPrimitivePort::connectPort(ptr(objects::CGeneralPort) component) {
					m_connectedPorts.push_back(component);
				}

				ptr(objects::CGeneralPort) CPrimitivePort::getConnectedPortAt(size_t index) {
					if (index < m_connectedPorts.size()) {
						return m_connectedPorts.at(index);
					}
					// throw
					return nullptr;
				}

				void CPrimitivePort::connectService(std::shared_ptr<objects::CGeneralService> service) {
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

                                std::shared_ptr<objects::CGeneralService> CPrimitivePort::getConnectedServiceByName(const std::string& name) {
                                    auto it = std::find_if(m_connectedServices.begin(), m_connectedServices.end(), [&name](ptr(CGeneralService) service) {
                                        if (service->isPrimitive()) {
                                            return service->getPrimitiveService()->getName() == name;
                                        }
                                        else {
                                            //return service->getService()->getPortByName("serviceSign")->
                                            return false;
                                        }
                                    });
                                    
                                    if (it == m_connectedServices.end()) {
					//throw exception
                                    }
                                    return *it;
                                }

				void CPrimitivePort::disconnect(size_t index) {
					if (index < m_connectedPorts.size()) {
						m_connectedPorts[index] = nullptr;
					}
				}

			}

		}
	}
}