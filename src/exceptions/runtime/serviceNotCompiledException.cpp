#include "exceptions/runtime/serviceNotCompiledException.h"

namespace exceptions {

	namespace runtime {

		CServiceNotCompiledException::CServiceNotCompiledException(const std::string& name)
			: CAbstractException("Service '" + name + "' not compiled!") {
		}

		const char* CServiceNotCompiledException::what() const throw() {
			return m_msg.c_str();
		}

	}

}