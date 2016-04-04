#pragma once

#include <vector>

#include "definitions/allDefinitions.h"
#include "types.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			namespace primitives {
				class CPrimitivePort;
			}

			class CGeneralPort {
			  protected:
				ptr(CComponent) m_port;

				ptr(primitives::CPrimitivePort) m_primitivePort;

				types::visibilityType m_visibility;

				types::roleType m_type;

				bool m_primitive;

			  public:
				CGeneralPort(ptr(CComponent) port,
				             types::visibilityType v = types::visibilityType::EXTERNAL,
				             types::roleType t = types::roleType::PROVIDES);

				CGeneralPort(ptr(primitives::CPrimitivePort) port,
				             types::visibilityType v = types::visibilityType::EXTERNAL,
				             types::roleType t = types::roleType::PROVIDES);

				CGeneralPort(ptr(CGeneralPort) instance);

				types::visibilityType getVisibility() const;

				types::roleType getRole() const;

				bool isPrimitive() const;

				ptr(CComponent) getPort();

				ptr(primitives::CPrimitivePort) getPrimitivePort();

				std::string getName() const;

				ptr(CComponent) getOwner();
			};
		}
	}
}
