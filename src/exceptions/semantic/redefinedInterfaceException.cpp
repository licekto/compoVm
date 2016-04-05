#include "exceptions/semantic/redefinedInterfaceException.h"

namespace exceptions {

	namespace semantic {

		CRedefinedInterfaceException::CRedefinedInterfaceException(const std::string& name)
			: CAbstractRedefinedException(name, "Interface") {
		}

		const char* CRedefinedInterfaceException::what() const throw() {
			return m_msg.c_str();
		}
	}

}