#pragma once

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {
                    
                    namespace primitives {
                        class CPrimitiveService;
                    }

			class CComponent;
                        
                        class CGeneralService {
                        private:
                            ptr(CComponent) m_service;
                            
                            ptr(primitives::CPrimitiveService) m_primitiveService;
                            
                            bool m_primitive;
                            
                        public:
                            CGeneralService(ptr(CComponent) service = nullptr);
                            
                            CGeneralService(ptr(primitives::CPrimitiveService) primitiveService = nullptr);
                            
                            CGeneralService(ptr(CGeneralService) instance);
                            
                            ptr(CComponent) getService();
                            
                            ptr(primitives::CPrimitiveService) getPrimitiveService();
                            
                            bool isPrimitive() const;
                            
                            std::string getName() const;
                        };
		}
	}
}
