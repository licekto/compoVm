#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

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

                        ptr(CPrimitivePort) CComponent::getPrimitivePortByName(const std::string& name) {
                            auto it = std::find_if(m_ports.begin(), m_ports.end(), [&name](ptr(TPortProperties) port) {
                                return port->m_primitivePort.use_count() && port->m_primitivePort->getName() == name;
                            });
                            
                            if (it == m_ports.end()) {
                                //throw exception
                            }
                            return (*it)->m_primitivePort;
                        }

			void CComponent::addService(std::shared_ptr<CComponent> service) {
                            m_services.push_back(service);
			}
                        
		}
	}
}