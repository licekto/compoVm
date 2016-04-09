#pragma once

#include <map>
#include <functional>

#include <boost/log/trivial.hpp>
#include <boost/log/sources/basic_logger.hpp>

#include "definitions/memoryObjectsDefinitions.h"

#include "types.h"
#include "interpreter/config.h"
//#include "interpreter/core/interpreter.h"
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

		class CBootstrap {
		  private:
			ptr(core::CCoreModules) m_coreModules;

			//ptr(core::CInterpreter) m_interpreter;

			void addPrimitiveServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor,
			                          std::map<std::string, ptr(mem_primitiveservice)>& servicesNames);

			void addPrimitivePorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> prepareSymbolSetter(const std::string& portName);

			std::function<ptr(mem_port)(const std::vector<ptr(mem_component)>&, const ptr(mem_component)&)> prepareSymbolGetter(const std::string& portName);

			void addDefaultPort(ptr(mem_value) value);
                        
                        ptr(mem_component) bootstrapPrologueWithComponent(ptr(ast_descriptor) descriptor, std::map<std::string, ptr(mem_primitiveservice)>& servicesNames, ptr(mem_component) owner);
                        
                        ptr(mem_component) bootstrapPrologue(ptr(ast_descriptor) descriptor, std::map<std::string, ptr(mem_primitiveservice)>& servicesNames);
                        
                        void bootstrapEpilogue(ptr(mem_component) component, std::map<std::string,std::shared_ptr<mem_primitiveservice> >& servicesNames);
                        
                        void addPorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor);
                        
                        void addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

                public:
                        CBootstrap(ptr(core::CCoreModules) coreModules = nullptr/*, const ptr(core::CInterpreter)& interpreter = nullptr*/);
                        
			ptr(mem_uint) bootstrapUIntValue(u64 value);

			ptr(mem_string) bootstrapStringValue(const std::string& value);

			ptr(mem_bool) bootstrapBoolValue(bool value);
                        
			ptr(mem_component) bootstrapComponent(ptr(mem_component) owner);

			ptr(mem_component) bootstrapPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner);

			ptr(mem_component) bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner);

			ptr(mem_component) bootstrapServiceComponent(ptr(ast_service) astService, ptr(mem_component) owner);

			ptr(mem_component) bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature, ptr(mem_component) owner);

			ptr(mem_component) bootstrapPortDescriptionComponent(ptr(ast_port) astPort, ptr(mem_component) owner);

			ptr(mem_component) bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind, ptr(mem_component) owner);

			ptr(mem_component) bootstrapInterfaceComponent(ptr(ast_port) astPort, ptr(mem_component) owner, ptr(mem_component) portOwner);

			ptr(mem_component) bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor);
		};
	}
}