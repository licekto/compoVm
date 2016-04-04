#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CBoolComponent : public CValueComponent {
				  private:
					bool m_value;

				  public:
					CBoolComponent(bool value = true);

					CBoolComponent(ptr(CBoolComponent) instance);

					virtual ~CBoolComponent();

					bool getValue();

					void setValue(bool value);
				};
			}
		}
	}
}