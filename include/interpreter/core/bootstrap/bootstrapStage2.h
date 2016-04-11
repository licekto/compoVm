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

				ptr(mem_component) cloneInterface(ptr(mem_component) interface);

			  public:
				CBootstrapStage2(ptr(CBootstrapStage1) stage1 = nullptr);

				ptr(mem_component) bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor);
			};

		}

	}
}