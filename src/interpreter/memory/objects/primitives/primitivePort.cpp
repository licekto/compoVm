#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CPrimitivePort::CPrimitivePort(const std::string& name, std::shared_ptr<objects::CComponent> owner, bool collection)
					: CAbstractPrimitive(name, owner), m_isDelegated(false), m_isCollection(collection) {
				}

				CPrimitivePort::CPrimitivePort(ptr(CPrimitivePort) instance)
					: CAbstractPrimitive(instance) {
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
					ptr(objects::CGeneralPort) port;
					try {
						port = m_connectedPorts.at(index).lock();
					} catch (const std::out_of_range& ex) {
						TRACE(ERROR, "Connected ports index out of range exception, index: " << index << ", exception: '" << ex.what() << "'");
					}
					return port;
				}

				void CPrimitivePort::connectService(std::shared_ptr<objects::CGeneralService> service) {
					m_connectedServices.push_back(service);
				}

				size_t CPrimitivePort::getConnectedServicesNumber() const {
					return m_connectedServices.size();
				}

				ptr(objects::CGeneralService) CPrimitivePort::getConnectedServiceAt(size_t index) {
					ptr(objects::CGeneralService) service;
					try {
						service = m_connectedServices.at(index).lock();
					} catch (const std::out_of_range& ex) {
						TRACE(ERROR, "Connected services index out of range exception, index: " << index << ", exception: '" << ex.what() << "'");
					}
					return service;
				}

				std::shared_ptr<objects::CGeneralService> CPrimitivePort::getConnectedServiceByName(const std::string& name) {
					auto it = std::find_if(m_connectedServices.begin(), m_connectedServices.end(), [&name](wptr(CGeneralService) service) {
						return service.lock()->getName() == name;
					});

					if (it == m_connectedServices.end()) {
						throw exceptions::runtime::CServiceNotFoundException(name);
					}
					//return *it.base()->lock();
                                        return it.base()->lock();
				}

				void CPrimitivePort::disconnectPortAt(size_t index) {
					try {
						if (m_connectedPorts.size()) {
							m_connectedPorts.erase(m_connectedPorts.begin()+index);
						}
					} catch (const std::out_of_range& ex) {
						TRACE(ERROR, "Connected ports index out of range exception, index: " << index << ", exception: '" << ex.what() << "'");
					}
                                }

                                void CPrimitivePort::disconnectAll() {
                                    m_connectedPorts.clear();
                                }

				void CPrimitivePort::disconnectServiceByName(const std::string& name) {
					auto it = std::find_if(m_connectedServices.begin(), m_connectedServices.end(), [&name](wptr(CGeneralService) service) {
						return service.lock()->getName() == name;
					});

					if (it != m_connectedServices.end()) {
						m_connectedServices.erase(it);
					}
                                }

                                void CPrimitivePort::delegateToPort(ptr(objects::CGeneralPort) port) {
                                        m_isDelegated = true;
                                        m_delegatedPort = port;
                                }

                                ptr(objects::CGeneralPort) CPrimitivePort::getDelegatedPort() {
                                        return m_delegatedPort.lock();
                                }

                                bool CPrimitivePort::isDelegated() const {
                                        return m_isDelegated;
                                }

                                bool CPrimitivePort::isCollection() const {
                                        return m_isCollection;
                                }

			}

		}
	}
}