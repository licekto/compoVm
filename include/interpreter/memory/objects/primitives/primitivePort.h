#pragma once

#include <string>
#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/generalService.h"
#include "interpreter/memory/objects/generalPort.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			namespace primitives {

				class CPrimitivePort : public CAbstractPrimitive {
				  private:
					std::vector<ptr(objects::CGeneralPort)> m_connectedPorts;
                                        
                                        std::vector<ptr(objects::CGeneralService)> m_connectedServices;

				  public:
					CPrimitivePort(const std::string& name = "", ptr(objects::CComponent) owner = nullptr);
                                        
                                        CPrimitivePort(ptr(CPrimitivePort) instance);

					virtual ~CPrimitivePort();

                                        size_t getConnectedPortsNumber() const;
                                        
					void connectPort(ptr(objects::CGeneralPort) component);

					ptr(objects::CGeneralPort) getConnectedPortAt(size_t index);
                                        
                                        size_t getConnectedServicesNumber() const;
                                        
                                        void connectService(ptr(objects::CGeneralService) service);
                                        
                                        ptr(objects::CGeneralService) getConnectedServiceAt(size_t index);
				};

			}

		}
	}
}