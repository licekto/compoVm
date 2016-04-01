#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/valueComponent.h"
#include "types.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CUnsignedIntComponent : public CValueComponent {
			  private:
				u64 m_value;

			  public:
                              
                                virtual ~CUnsignedIntComponent();
                              
				CUnsignedIntComponent(u64 value = 0);

				u64 getValue();

				void setValue(u64 value);
			};
		}
	}
}