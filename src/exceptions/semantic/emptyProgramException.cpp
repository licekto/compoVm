#include "exceptions/semantic/emptyProgramException.h"

namespace exceptions {

	namespace semantic {
		const char* CEmptyProgramException::what() const throw() {
			return "Empty program exception!";
		}
	}

}