#include "exceptions/runtime/kernelModuleNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CKernelModuleNotFoundException::CKernelModuleNotFoundException(std::string module)
			: CAbstractException("'" + module + "' kernel module not found!") {
		}

		const char* CKernelModuleNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}