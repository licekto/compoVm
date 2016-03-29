#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CValueComponent : public CComponent {

			  public:

                                virtual ~CValueComponent();
                              
				void setDefaultPort(ptr(CComponent) defaultPort) = delete;

				void setSelfPort(ptr(CComponent) selfPort) = delete;

				void setSuperPort(ptr(CComponent) superPort) = delete;

				void addPort(ptr(CComponent) port) = delete;

				void addService(ptr(CComponent) service) = delete;
			};
		}
	}
}