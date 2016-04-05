#include "exceptions/runtime/coreModuleNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CCoreModuleNotFoundException::CCoreModuleNotFoundException(const std::string& module)
			: CAbstractException("'" + module + "' kernel module not found!") {
		}

		const char* CCoreModuleNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}