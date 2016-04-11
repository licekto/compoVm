#pragma once

#include <map>
#include <functional>

#include "definitions/memoryObjectsDefinitions.h"

#include "types.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModules.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			class CBootstrapStage2 {
			  private:

			  public:
				CBootstrapStage2();

				ptr(mem_component) bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor);
			};

		}

	}
}