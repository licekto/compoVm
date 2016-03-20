#include "exceptions/semantic/undefinedInterfaceException.h"

namespace exceptions {

	namespace semantic {
            
                CUndefinedInterfaceException::CUndefinedInterfaceException(std::string name)
                        : CAbstractUndefinedException(name) {
                }
            
		const char* CUndefinedInterfaceException::what() const throw() {
                        std::string msg = "Interface ";
			msg += getPartialMessage();

			return msg.c_str();
		}
	}

}