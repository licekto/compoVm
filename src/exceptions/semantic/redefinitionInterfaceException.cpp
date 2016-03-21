#include "exceptions/semantic/redefinitionInterfaceException.h"

namespace exceptions {

	namespace semantic {

		CRedefinitionInterfaceException::CRedefinitionInterfaceException(std::string name)
			: CAbstractRedefinitionException(name, "Interface") {
		}

		const char* CRedefinitionInterfaceException::what() const throw() {
			return m_msg.c_str();
		}
	}

}