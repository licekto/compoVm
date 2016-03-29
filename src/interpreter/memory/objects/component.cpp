#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

                        CComponent::~CComponent() {
                        }

			void CComponent::addPort(ptr(TPortProperties) port) {
				m_ports.push_back(port);
			}

			size_t CComponent::getNumberOfPorts() const {
				return m_ports.size();
			}

			ptr(TPortProperties) CComponent::getPortAt(size_t index) {
				if (index < m_ports.size()) {
					return m_ports.at(index);
				}
				// throw exception
				return nullptr;
			}

			std::shared_ptr<primitives::CAbstractPrimitive> CComponent::getPrimitiveNamePort() {
				return getPrimitivePortByName(NAME_OF_NAMEPORT);
			}

			ptr(primitives::CAbstractPrimitive) CComponent::getPrimitivePortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](const ptr(TPortProperties)& port) {
					return port->m_primitivePort.use_count() && port->m_primitivePort->getName() == name;
				});

				if (it == m_ports.end()) {
					//throw exception
				}
				return (*it)->m_primitivePort;
			}

			std::shared_ptr<CComponent> CComponent::getPortByName(const std::string& name) {
				auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(TPortProperties) port) {
					return port->m_port.use_count() && port->m_port->getPrimitiveNamePort()->getName() == name;
				});

				if (it == m_ports.end()) {
					//throw exception
				}
				return (*it)->m_port;
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