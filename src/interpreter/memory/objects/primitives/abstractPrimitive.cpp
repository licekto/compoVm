#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CAbstractPrimitive::CAbstractPrimitive(const std::string& name, std::shared_ptr<CComponent> owner)
					: m_name(name), m_owner(owner) {
				}

				CAbstractPrimitive::~CAbstractPrimitive() {
				}

				std::string CAbstractPrimitive::getName() const {
					return m_name;
				}

				std::shared_ptr<CComponent> CAbstractPrimitive::getOwner() {
					return m_owner;
				}

			}

		}
	}
}