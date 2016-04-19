#pragma once

#include <map>
#include <functional>

#include "definitions/memoryObjectsDefinitions.h"

#include "types.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/memory/objects/component.h"
#include "interpreter/memory/objects/values/signedIntegerComponent.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "interpreter/memory/objects/values/boolComponent.h"
#include "interpreter/memory/objects/primitives/abstractPrimitive.h"
#include "interpreter/memory/objects/primitives/primitiveService.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "exceptions/semantic/unsupportedFeatureException.h"
#include "exceptions/runtime/unknownPortTypeException.h"
#include "exceptions/runtime/wrongPortTypeException.h"
#include "exceptions/runtime/unknownAstNodeTypeException.h"
#include "ast/visitor/constantsVisitor.h"

namespace interpreter {

	namespace core {

		class CInterpreter;

		namespace bootstrap {

			class CBootstrapStage1 {
			  private:
				friend class CBootstrapStage2;

				ptr(core::CCoreModules) m_coreModules;

				ptr(core::CInterpreter) m_interpreter;
                                
                        public:
				void addPrimitiveServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor, std::map<std::string, ptr(mem_primitiveservice)>& servicesNames);

				void addPrimitivePorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

				std::function<ptr(mem_port)(const ptr(mem_component)&)> prepareStringSetter(const std::string& portName);

				std::function<ptr(mem_port)(const ptr(mem_component)&)> prepareStringGetter(const std::string& portName);

				void addDefaultPort(ptr(mem_value) value);
                                
				ptr(mem_component) bootstrapPrologueWithComponent(ptr(ast_descriptor) descriptor, std::map<std::string, ptr(mem_primitiveservice)>& servicesNames, ptr(mem_component) owner);

				ptr(mem_component) bootstrapPrologue(ptr(ast_descriptor) descriptor, std::map<std::string, ptr(mem_primitiveservice)>& servicesNames);

				void bootstrapEpilogue(ptr(mem_component) component, std::map<std::string,std::shared_ptr<mem_primitiveservice> >& servicesNames);

			  public:
				CBootstrapStage1(ptr(core::CCoreModules) coreModules = nullptr, ptr(core::CInterpreter) interpreter = nullptr);
                                
                                void setInterpreter(ptr(core::CInterpreter) interpreter);

				ptr(mem_int) bootstrapIntValue(i64 value);

				ptr(mem_string) bootstrapStringValue(const std::string& value);

				ptr(mem_bool) bootstrapBoolValue(bool value);

				ptr(mem_component) bootstrapComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner);

				ptr(mem_component) bootstrapPortComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapCollectionPortComponent(ptr(ast_port) astPort, ptr(mem_component) owner);
                                
                                ptr(mem_component) bootstrapCollectionPortComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapServiceComponent(ptr(ast_service) astService, ptr(mem_component) owner);
                                
                                ptr(mem_component) bootstrapServiceComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapServiceSignatureComponent(ptr(ast_servicesignature) astSignature, ptr(mem_component) owner);

				ptr(mem_component) bootstrapServiceSignatureComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapPortDescriptionComponent(ptr(ast_port) astPort, ptr(mem_component) owner);

				ptr(mem_component) bootstrapServiceInvocationComponent(ptr(ast_serviceinvocation) astServiceInv, ptr(mem_component) owner);

				ptr(mem_component) bootstrapConnectionDescriptionComponent(ptr(ast_bind) bind, ptr(mem_component) owner);

				ptr(mem_component) bootstrapInterfaceComponent(ptr(mem_component) owner);

				ptr(mem_component) bootstrapInterfaceComponent(ptr(ast_port) astPort, ptr(mem_component) owner, ptr(mem_component) portOwner);
			};

		}

	}
}