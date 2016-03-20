#include "exceptions/semantic/undefinedSymbolException.h"

namespace exceptions {

	namespace semantic {
            
                CUndefinedSymbolException::CUndefinedSymbolException(std::string name)
                        : CAbstractUndefinedException(name) {
                }
            
		const char* CUndefinedSymbolException::what() const throw() {
                        std::string msg = "Symbol ";
			msg += getPartialMessage();

			return msg.c_str();
		}
	}

}