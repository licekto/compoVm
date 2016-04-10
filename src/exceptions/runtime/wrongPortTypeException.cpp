#include "exceptions/runtime/wrongPortTypeException.h"

namespace exceptions {

	namespace runtime {

		CWrongPortTypeException::CWrongPortTypeException(const std::string& type, const std::string& service)
			: CAbstractException("Wrong port type '" + type + "' while calling service '" + service + "'!") {
		}

		const char* CWrongPortTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}