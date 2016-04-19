#include "exceptions/runtime/memoryNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CMemoryNotFoundException::CMemoryNotFoundException()
			: CAbstractException("Memory module not found!") {
		}

		const char* CMemoryNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}