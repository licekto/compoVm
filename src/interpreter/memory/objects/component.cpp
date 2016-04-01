#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePortProperties.h"
#include "interpreter/memory/objects/portProperties.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                        CComponent::~CComponent() {
                        }

			void CComponent::addPort(ptr(CAbstractPortProperties) port) {
				m_ports.push_back(port);
                        }

			size_t CComponent::getNumberOfPorts() const {
				return m_ports.size();
                        }

			ptr(CAbstractPortProperties) CComponent::getPortAt(size_t index) {
				if (index < m_ports.size()) {
					return m_ports.at(index);
				}
				// throw exception
				return nullptr;
                        }

			ptr(primitives::CPrimitivePortProperties) CComponent::getPrimitiveNamePort() {
				return cast(primitives::CPrimitivePortProperties)(getPortByName(NAME_OF_NAMEPORT));
			}

			ptr(CAbstractPortProperties) CComponent::getPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(CAbstractPortProperties) port) {
                                    if (port->isPrimitive()) {
                                        return cast(primitives::CPrimitivePortProperties)(port)->getPrimitivePort()->getName() == name;
                                    }
                                    else {
                                        return cast(CPortProperties)(port)->getPort()->getPrimitiveNamePort()->getPrimitivePort()->getName() == name;
                                    }
				});

				if (it == m_ports.end()) {
					//throw exception
				}
				return *it;
                                
                        }

                        std::shared_ptr<CComponent> CComponent::getServiceByName(const std::string& name) {
                                auto it = std::find_if(m_services.begin(), m_services.end(), [&name](ptr(CComponent) service) {
					//return port->m_port.use_count() && port->m_port->getPrimitiveNamePort()->getName() == name;
                                        return true;
				});

				if (it == m_services.end()) {
					//throw exception
				}
				return *it;
                        }

                        std::shared_ptr<primitives::CPrimitiveService> CComponent::getPrimitiveServiceByName(const std::string& name) {
                                auto it = std::find_if(m_primitiveServices.begin(), m_primitiveServices.end(), [&name](ptr(primitives::CPrimitiveService) service) {
					return service->getName() == name;
				});

				if (it == m_primitiveServices.end()) {
					//throw exception
				}
				return *it;
                        }

			void CComponent::addService(std::shared_ptr<CComponent> service) {
				m_services.push_back(service);
			}

			void CComponent::addPrimitiveService(std::shared_ptr<primitives::CPrimitiveService> service) {
				m_primitiveServices.push_back(service);
			}

		}
	}
}