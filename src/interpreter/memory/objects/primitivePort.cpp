#include "interpreter/memory/objects/primitivePort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			CPrimitivePort::CPrimitivePort(const std::string& name, std::shared_ptr<CComponent> owner)
				: m_name(name), m_owner(owner) {
			}

			std::string CPrimitivePort::getName() const {
				return m_name;
			}

			std::shared_ptr<CComponent> CPrimitivePort::getOwner() const {
				return m_owner;
			}
		}
	}
}