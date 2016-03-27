#pragma once

#include <map>
#include <functional>

#include "interpreter/core/coreModules.h"
#include "interpreter/core/coreModuleType.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/primitiveService.h"
#include "interpreter/memory/objects/stringComponent.h"
#include "interpreter/memory/objects/primitivePort.h"
#include "interpreter/memory/objects/primitiveCollectionPort.h"
#include "interpreter/core/native/newCall.h"

namespace interpreter {

	namespace memory {

		namespace manager {

			class CMemoryManager {
                        private:
                            ptr(core::CCoreModules) m_coreModules;
                            
                            std::map<core::coreModuleType, ptr(objects::CComponent)> m_coreComponentsMap;
                            
                            void iterateAddPorts(ptr(ast_reqprov) reqprov, std::function<void(objects::visibility, objects::type, ptr(ast_port))> callback);
                            
                            void addPrimitivePorts(ptr(objects::CComponent) component, ptr(ast_descriptor) descriptor);
                            
                            ptr(objects::CComponent) bootstrapPortComponent(ptr(ast_port) astPort, ptr(objects::CComponent) owner);
                            
                            void addPorts(ptr(objects::CComponent) component, ptr(ast_descriptor) descriptor);
                            
                            ptr(objects::CComponent) bootstrapServiceComponent(ptr(ast_service) astService);
                            
                            ptr(objects::CComponent) bootstrapDescriptorComponent();
                            
                        public:
                            
                            CMemoryManager(ptr(core::CCoreModules) coreModules = nullptr);
                            
                            void boostrap();
			};

		}
	}
}