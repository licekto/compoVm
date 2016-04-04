#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace values {

				class CStringComponent : public CValueComponent {
				  private:
					std::string m_value;

				  public:
					CStringComponent(const std::string& value = "");

					CStringComponent(ptr(CStringComponent) instance);

					virtual ~CStringComponent();

					std::string getValue();

					void setValue(const std::string& value);
				};
			}
		}
	}
}