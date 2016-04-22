#include "exceptions/execution/continueException.h"

namespace exceptions {

	namespace execution {

		CContinueException::CContinueException()
			: CAbstractException("Continue exception.") {
		}

		const char* CContinueException::what() const throw() {
			return m_msg.c_str();
		}

	}

}