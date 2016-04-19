#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CValueComponent::CValueComponent(type_values type) : m_type(type) {
				}

				CValueComponent::~CValueComponent() {
				}

				void CValueComponent::addDefaultPort(std::shared_ptr<CGeneralPort> port) {
					m_ports.push_back(port);
				}

				ptr(CGeneralPort) CValueComponent::getDefaultPort() {
					return m_ports.at(0).lock();
				}

				ptr(CGeneralPort) CValueComponent::getPortByName(const std::string& name) {
					if (name != "default") {
                                            throw exceptions::runtime::CWrongValueComponentPortException(name);
					}
					return m_ports.at(0).lock();
                                }

                                type_values CValueComponent::getType() const {
                                        return m_type;
                                }

			}

		}
	}
}