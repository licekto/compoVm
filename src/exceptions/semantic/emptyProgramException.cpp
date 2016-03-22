#include "exceptions/semantic/emptyProgramException.h"

namespace exceptions {

	namespace semantic {

		CEmptyProgramException::CEmptyProgramException()
			: CAbstractException("Empty program exception!") {
		}

		const char* CEmptyProgramException::what() const throw() {
			return m_msg.c_str();
		}
	}

}