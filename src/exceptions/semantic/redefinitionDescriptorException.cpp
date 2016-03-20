#include "exceptions/semantic/redefinitionDescriptorException.h"

namespace exceptions {

	namespace semantic {
            
                CRedefinitionDescriptorException::CRedefinitionDescriptorException(std::string name)
                        : CAbstractRedefinitionException(name) {
                }
            
		const char* CRedefinitionDescriptorException::what() const throw() {
                        std::string msg = "Descriptor ";
			msg += getPartialMessage();

			return msg.c_str();
		}
	}

}