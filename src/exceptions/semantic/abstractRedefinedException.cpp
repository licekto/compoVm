#include "exceptions/semantic/abstractRedefinedException.h"

namespace exceptions {

	namespace semantic {

		CAbstractRedefinedException::CAbstractRedefinedException(std::string name, std::string element)
			: CAbstractException(element + " '" + name + "' redefined exception!") {
		}
	}

}