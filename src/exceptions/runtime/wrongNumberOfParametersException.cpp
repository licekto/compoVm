#include "exceptions/runtime/wrongNumberOfParametersException.h"

namespace exceptions {

	namespace runtime {

		CWrongNumberOfParametersException::CWrongNumberOfParametersException(const std::string& serviceName, size_t number)
			: CAbstractException("Wrong number of parameters: " + std::to_string(number) + " for service named '" + serviceName + "'!") {
		}

		const char* CWrongNumberOfParametersException::what() const throw() {
			return m_msg.c_str();
		}

	}

}