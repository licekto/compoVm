#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/valueComponent.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CStringComponent : public CValueComponent {
			  private:
				std::string m_value;

			  public:
                              
                                virtual ~CStringComponent();
                              
				CStringComponent(std::string value = "");

				std::string getValue();

				void setValue(std::string value);
			};
		}
	}
}