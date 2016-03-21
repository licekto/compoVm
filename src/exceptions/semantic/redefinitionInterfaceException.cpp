#include "exceptions/semantic/redefinitionInterfaceException.h"

namespace exceptions {

	namespace semantic {

		CRedefinitionInterfaceException::CRedefinitionInterfaceException(std::string name)
			: CAbstractRedefinitionException(name) {
		}

		const char* CRedefinitionInterfaceException::what() const throw() {
			std::string msg = "Interface ";
			msg += getPartialMessage();

			return msg.c_str();
		}
	}

}