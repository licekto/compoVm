#pragma once

#include <vector>
#include <algorithm>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/portProperties.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/config.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {
				class CPrimitiveService;
			}

			class CComponent {
			  private:

				std::vector<ptr(TPortProperties)> m_ports;

				std::vector<ptr(CComponent)> m_services;

				std::vector<ptr(primitives::CPrimitiveService)> m_primitiveServices;

			  public:

                                virtual ~CComponent();
                              
				void addPort(ptr(TPortProperties));

				size_t getNumberOfPorts() const;

				ptr(TPortProperties) getPortAt(size_t index);

				ptr(primitives::CAbstractPrimitive) getPrimitiveNamePort();

				ptr(primitives::CAbstractPrimitive) getPrimitivePortByName(const std::string& name);

				ptr(CComponent) getPortByName(const std::string& name);

				void addService(ptr(CComponent) service);

				void addPrimitiveService(ptr(primitives::CPrimitiveService) service);
			};

		}
	}
}
