#include "exceptions/semantic/redefinedPortException.h"

namespace exceptions {

	namespace semantic {

		CRedefinedPortException::CRedefinedPortException(const std::string& name)
			: CAbstractRedefinedException(name, "Port") {
		}

		const char* CRedefinedPortException::what() const throw() {
			return m_msg.c_str();
		}
	}

}