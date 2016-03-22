#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		CAbstractUndefinedException::CAbstractUndefinedException(std::string name, std::string element)
			: CAbstractException(element + " '" + name + "' undefined exception!") {
		}
	}

}