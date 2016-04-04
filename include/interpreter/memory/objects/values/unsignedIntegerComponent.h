#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/valueComponent.h"
#include "types.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CUnsignedIntegerComponent : public CValueComponent {
				  private:
					u64 m_value;

				  public:

					CUnsignedIntegerComponent(u64 value = 0);

					CUnsignedIntegerComponent(ptr(CUnsignedIntegerComponent) instance);

					virtual ~CUnsignedIntegerComponent();

					u64 getValue();

					void setValue(u64 value);
				};
			}
		}
	}
}