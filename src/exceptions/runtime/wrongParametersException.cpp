#include "exceptions/runtime/wrongParametersException.h"

namespace exceptions {

	namespace runtime {

		CWrongParametersException::CWrongParametersException(const std::string& msg)
			: CAbstractException(msg) {
		}

		const char* CWrongParametersException::what() const throw() {
			return m_msg.c_str();
		}

	}

}