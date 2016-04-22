#include "exceptions/execution/breakException.h"

namespace exceptions {

	namespace execution {

		CBreakException::CBreakException()
			: CAbstractException("Break exception.") {
		}

		const char* CBreakException::what() const throw() {
			return m_msg.c_str();
		}

	}

}