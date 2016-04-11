#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				CValueComponent::CValueComponent() {
				}

				CValueComponent::CValueComponent(ptr(CValueComponent) instance)
					: CComponent(instance) {
				}

				CValueComponent::~CValueComponent() {
				}

				void CValueComponent::addDefaultPort(std::shared_ptr<CGeneralPort> port) {
					m_ports.push_back(port);
				}

				ptr(CGeneralPort) CValueComponent::getDefaultPort() {
					return m_ports.at(0);
				}

				ptr(CGeneralPort) CValueComponent::getPortByName(const std::string& name) {
					if (name != "default") {
						// throw
						return nullptr;
					}
					return m_ports.at(0);
				}

			}

		}
	}
}