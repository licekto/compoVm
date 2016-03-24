#pragma once

#include "interpreter/core/coreModules.h"
#include "interpreter/core/coreModuleType.h"

namespace interpreter {

	namespace memory {

		namespace manager {

			class CManager {
			  private:
				ptr(core::CCoreModules) m_coreModules;

			  public:

				CManager(ptr(core::CCoreModules) coreModules);
                                
                                void bootstrap();
			};

		}
	}
}