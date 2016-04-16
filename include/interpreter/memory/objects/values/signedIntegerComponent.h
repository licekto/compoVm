#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/valueComponent.h"
#include "types.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CSignedIntegerComponent : public CValueComponent {
				  private:
					i64 m_value;

				  public:

					CSignedIntegerComponent(i64 value = 0);

					CSignedIntegerComponent(ptr(CSignedIntegerComponent) instance);

					virtual ~CSignedIntegerComponent();

					i64 getValue();

					void setValue(i64 value);
				};
			}
		}
	}
}