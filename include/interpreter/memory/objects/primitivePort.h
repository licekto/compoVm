#pragma once

#include <string>

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                        class CComponent;

			class CPrimitivePort : public std::enable_shared_from_this<CPrimitivePort> {
			  private:
				std::string m_name;

				ptr(CComponent) m_owner;
                                
                                ptr(CComponent) m_connectedComponent;

			  public:
				CPrimitivePort(const std::string& name = "", ptr(CComponent) owner = nullptr, ptr(CComponent) connected = nullptr);

				std::string getName() const;

				ptr(CComponent) getOwner();
                                
                                void setConnectedComponent(ptr(CComponent) component);
                                
                                ptr(CComponent) getConnectedComponent();
			};

		}
	}
}