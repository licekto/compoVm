#include "exceptions/semantic/undefinedDescriptorException.h"

namespace exceptions {

	namespace semantic {
            
                CUndefinedDescriptorException::CUndefinedDescriptorException(std::string name)
                        : CAbstractUndefinedException(name) {
                }
            
		const char* CUndefinedDescriptorException::what() const throw() {
                        std::string msg = "Descriptor ";
			msg += getPartialMessage();

			return msg.c_str();
		}
	}

}