#include "exceptions/runtime/wrongNumberOfParametersException.h"

namespace exceptions {

	namespace runtime {

		CWrongNumberOfParametersException::CWrongNumberOfParametersException(size_t number)
			: CAbstractException("Wrong number of parameters: " + std::to_string(number) + "!") {
		}

		const char* CWrongNumberOfParametersException::what() const throw() {
			return m_msg.c_str();
		}

	}

}