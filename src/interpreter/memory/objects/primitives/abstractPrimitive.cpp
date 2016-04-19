#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				CAbstractPrimitive::CAbstractPrimitive(const std::string& name, ptr(CComponent) owner)
					: m_name(name), m_owner(owner) {
				}

				CAbstractPrimitive::CAbstractPrimitive(ptr(CAbstractPrimitive) instance)
					: m_name(instance->m_name) {

				}

				CAbstractPrimitive::~CAbstractPrimitive() {
				}

				std::string CAbstractPrimitive::getName() const {
					return m_name;
				}

				ptr(CComponent) CAbstractPrimitive::getOwner() {
					return m_owner;
				}

				void CAbstractPrimitive::setOwner(ptr(CComponent) owner) {
					//m_owner = wptr(CComponent)(owner);
                                    m_owner = owner;
                                }

                                std::string CAbstractPrimitive::printExpired() const {
//                                    if (m_owner.expired()) {
//                                        return "EXPIRED";
//                                    }
//                                    else {
//                                        return "VALID";
//                                    }
                                    return "";
                                }

			}

		}
	}
}