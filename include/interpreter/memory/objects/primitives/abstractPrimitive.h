#pragma once

#include <string>

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			namespace primitives {

				class CAbstractPrimitive {
				  protected:
					std::string m_name;

					wptr(CComponent) m_owner;

				  public:
					CAbstractPrimitive(const std::string& name = "", ptr(CComponent) owner = nullptr);

					CAbstractPrimitive(ptr(CAbstractPrimitive) instance);

					virtual ~CAbstractPrimitive();

					std::string getName() const;

					ptr(CComponent) getOwner();

					void setOwner(ptr(CComponent) owner);
				};

			}

		}
	}
}