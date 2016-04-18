#include "exceptions/runtime/wrongBindTypeException.h"

namespace exceptions {

	namespace runtime {

		CWrongBindTypeException::CWrongBindTypeException(const std::string& bindType)
			: CAbstractException("Wrong bind type: '" + bindType + "'!") {
		}

		const char* CWrongBindTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}