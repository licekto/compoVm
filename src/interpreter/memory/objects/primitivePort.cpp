#include "interpreter/memory/objects/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CPrimitivePort::CPrimitivePort(const std::string& name, std::shared_ptr<CComponent> owner, ptr(CComponent) connected)
				: m_name(name), m_owner(owner), m_connectedComponent(connected) {
			}

			std::string CPrimitivePort::getName() const {
				return m_name;
			}

			std::shared_ptr<CComponent> CPrimitivePort::getOwner() {
				return m_owner;
                        }

                        void CPrimitivePort::setConnectedComponent(std::shared_ptr<CComponent> component) {
                            m_connectedComponent = component;
                        }

                        std::shared_ptr<CComponent> CPrimitivePort::getConnectedComponent() {
                            m_connectedComponent;
                        }

		}
	}
}