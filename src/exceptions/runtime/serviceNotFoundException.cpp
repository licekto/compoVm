#include "exceptions/runtime/serviceNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CServiceNotFoundException::CServiceNotFoundException(const std::string& name)
			: CAbstractException("Service '" + name + "' not found!") {
		}

		const char* CServiceNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}