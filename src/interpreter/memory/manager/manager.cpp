#include "interpreter/memory/manager/manager.h"

namespace interpreter {

	namespace memory {

		namespace manager {

			CManager::CManager(ptr(core::CCoreModules) coreModules)
                        : m_coreModules(coreModules) {
			}

                        void CManager::bootstrap() {
                        }
                        
		}
	}
}