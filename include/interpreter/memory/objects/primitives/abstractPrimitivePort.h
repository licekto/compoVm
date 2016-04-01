#pragma once

#include <string>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			namespace primitives {

				class CAbstractPrimitivePort : public CAbstractPrimitive {
				  public:
					CAbstractPrimitivePort(const std::string& name = "", ptr(objects::CComponent) owner = nullptr);

					virtual ~CAbstractPrimitivePort() = 0;
				};

			}

		}
	}
}