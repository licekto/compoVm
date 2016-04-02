#pragma once

#include <string>
#include <vector>

#include "definitions/allDefinitions.h"
#include "interpreter/memory/objects/primitives/abstractPrimitivePort.h"
#include "interpreter/memory/objects/generalService.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent;

			namespace primitives {

				class CPrimitivePort : public CAbstractPrimitivePort {
				  private:
					ptr(objects::CComponent) m_connectedComponent;
                                        
                                        std::vector<ptr(objects::CGeneralService)> m_connectedServices;

				  public:
					CPrimitivePort(const std::string& name = "", ptr(objects::CComponent) owner = nullptr, ptr(objects::CComponent) connected = nullptr);

					virtual ~CPrimitivePort();

					void setConnectedComponent(ptr(objects::CComponent) component);

					ptr(objects::CComponent) getConnectedComponent();
                                        
                                        void setConnectedService(ptr(objects::CGeneralService) service);
                                        
                                        size_t getConnectedServicesNumber() const;
                                        
                                        ptr(objects::CGeneralService) getConnectedServiceAt(size_t index);
				};

			}

		}
	}
}