#pragma once

#include <string>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			namespace primitives {

				class CPrimitivePort : public CAbstractPrimitive {
				  private:
					ptr(objects::CComponent) m_connectedComponent;

				  public:
					CPrimitivePort(const std::string& name = "", ptr(objects::CComponent) owner = nullptr, ptr(objects::CComponent) connected = nullptr);

					virtual ~CPrimitivePort();

					void setConnectedComponent(ptr(objects::CComponent) component);

					ptr(objects::CComponent) getConnectedComponent();
				};

			}

		}
	}
}