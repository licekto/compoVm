#include "exceptions/runtime/wrongStringOperationException.h"

namespace exceptions {

	namespace runtime {

		CWrongStringOperationException::CWrongStringOperationException()
			: CAbstractException("Wrong string operation, only concatenation (+) allowed!") {
		}

		const char* CWrongStringOperationException::what() const throw() {
			return m_msg.c_str();
		}

	}

}