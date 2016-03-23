#pragma once

#include <string>

#include "definitions.h"
#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CPrimitivePort : public std::enable_shared_from_this<CPrimitivePort> {
			  private:
				std::string m_name;

				ptr(CComponent) m_owner;

			  public:
				CPrimitivePort(const std::string& name, ptr(CComponent) owner);

				std::string getName() const;

				ptr(CComponent) getOwner() const;
			};

		}
	}
}