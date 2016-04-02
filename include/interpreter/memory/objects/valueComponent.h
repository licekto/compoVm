#pragma once

#include <string>

#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitives/primitivePortProperties.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CValueComponent : public CComponent {
                        protected:
                            
			  public:

                                virtual ~CValueComponent();
                              
				void addPort(ptr(CAbstractPortProperties) port) = delete;

				size_t getNumberOfPorts() const = delete;

				ptr(CAbstractPortProperties) getPortAt(size_t index) = delete;

				ptr(primitives::CPrimitivePortProperties) getPrimitiveNamePort() = delete;

				ptr(CAbstractPortProperties) getPortByName(const std::string& name) = delete;
                                
                                ptr(CComponent) getServiceByName(const std::string& name) = delete;
                                
                                ptr(primitives::CPrimitiveService) getPrimitiveServiceByName(const std::string& name) = delete;

				void addService(ptr(CComponent) service) = delete;

				void addPrimitiveService(ptr(primitives::CPrimitiveService) service) = delete;
			};
		}
	}
}