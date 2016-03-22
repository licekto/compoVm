#include "exceptions/semantic/undefinedPortException.h"

namespace exceptions {

	namespace semantic {

		CUndefinedPortException::CUndefinedPortException(std::string name)
			: CAbstractUndefinedException(name, "Port") {
		}

		const char* CUndefinedPortException::what() const throw() {
			return m_msg.c_str();
		}
	}

}