#pragma once

#include <map>
#include <functional>

#include "types.h"
#include "interpreter/config.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/coreModuleType.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/unsignedIntegerComponent.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "interpreter/memory/objects/values/boolComponent.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"

namespace interpreter {

	namespace core {

		class CInterpreter;

		class CBootstrap {
		  private:
			ptr(core::CCoreModules) m_coreModules;

			ptr(core::CInterpreter) m_interpreter;

			std::map<core::coreModuleType, ptr(memory::objects::CComponent)> m_coreComponentsMap;

			void addPrimitiveServices(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor,
			                          std::map<std::string, ptr(memory::objects::primitives::CPrimitiveService)>& servicesNames);

			void addPrimitivePorts(ptr(memory::objects::CComponent) component, ptr(ast_descriptor) descriptor);

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> prepareSymbolSetter(const std::string& portName);

			std::function<ptr(memory::objects::CComponent)(const std::vector<ptr(memory::objects::CComponent)>&, const ptr(memory::objects::CComponent)&)> prepareSymbolGetter(const std::string& portName);

			void addDefaultPort(ptr(memory::objects::values::CValueComponent) value);

                public:
                        
			ptr(memory::objects::values::CUnsignedIntegerComponent) bootstrapUIntValue(u64 value);

			ptr(memory::objects::values::CStringComponent) bootstrapStringValue(const std::string& value);

			ptr(memory::objects::values::CBoolComponent) bootstrapBoolValue(bool value);
                        
			ptr(memory::objects::CComponent) bootstrapComponent();

			ptr(memory::objects::CComponent) bootstrapPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner);

			ptr(memory::objects::CComponent) bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(memory::objects::CComponent) owner);

			ptr(memory::objects::CComponent) bootstrapServiceComponent(ptr(ast_service) astService, ptr(memory::objects::CComponent) context);

			ptr(memory::objects::CComponent) bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature);

			ptr(memory::objects::CComponent) bootstrapPortDescriptionComponent(ptr(ast_port) astPort);

			ptr(memory::objects::CComponent) bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind);

			ptr(memory::objects::CComponent) bootstrapInterfaceComponent(ptr(ast_port) astPort);

			ptr(memory::objects::CComponent) bootstrapDescriptorComponent();

			CBootstrap(ptr(core::CCoreModules) coreModules = nullptr, const ptr(core::CInterpreter)& interpreter = nullptr);

			void boostrap();

			ptr(memory::objects::CComponent) getCoreComponent(core::coreModuleType type);
		};
	}
}