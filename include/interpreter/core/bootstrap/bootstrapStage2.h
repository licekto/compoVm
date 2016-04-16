#pragma once

#include <map>
#include <functional>

#include "definitions/memoryObjectsDefinitions.h"

#include "types.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModules.h"
#include "bootstrapStage1.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			class CBootstrapStage2 {
			  private:
				ptr(CBootstrapStage1) m_bootstrapStage1;

				void addPorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

				void addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

				ptr(mem_component) bootstrapRootComponent(ptr(mem_component) owner);

				ptr(mem_component) buildPortFromDescription(ptr(mem_component) description, ptr(mem_component) owner);

				ptr(mem_component) cloneInterface(ptr(mem_component) interface, ptr(mem_component) portOwner);
                                
                                ptr(mem_component) cloneSignature(ptr(mem_component) signature, ptr(mem_component) owner);
                                
                                ptr(mem_component) cloneService(ptr(mem_component) service, ptr(mem_component) owner);

			  public:
				CBootstrapStage2(ptr(CBootstrapStage1) stage1 = nullptr);
                                
                                ptr(mem_port) getIntComponent(i64 value);
                                
                                ptr(mem_port) getStringComponent(const std::string& value);
                                
                                ptr(mem_port) getBoolComponent(bool value);

				ptr(mem_component) bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor);
			};

		}

	}
}