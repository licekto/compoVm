#pragma once

#include <map>
#include <functional>

#include "interpreter/core/coreModules.h"
#include "interpreter/core/coreModuleType.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/stringComponent.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/primitives/primitiveCollectionPort.h"

namespace interpreter {

	namespace core {

			class CMemoryManager {
                        private:
                            ptr(core::CCoreModules) m_coreModules;
                            
                            std::map<core::coreModuleType, ptr(memory::objects::CComponent)> m_coreComponentsMap;
                            
                            void iterateAddPorts(ptr(ast_reqprov) reqprov, std::function<void(memory::objects::portVisibility, memory::objects::portType, ptr(ast_port))> callback);
                            
                            void addPrimitivePorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor);
                            
                            ptr(memory::objects::CComponent) bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner);
                            
                            void addPorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor);
                            
                            ptr(memory::objects::CComponent) bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context);
                            
                            ptr(memory::objects::CComponent) bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature);
                            
                            ptr(memory::objects::CComponent) bootstrapDescriptorComponent();
                            
                        public:
                            
                            CMemoryManager(ptr(core::CCoreModules) coreModules = nullptr);
                            
                            void boostrap();
			};
	}
}