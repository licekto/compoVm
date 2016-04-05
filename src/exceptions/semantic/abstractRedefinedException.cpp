#include "exceptions/semantic/abstractRedefinedException.h"

namespace exceptions {

	namespace semantic {

		CAbstractRedefinedException::CAbstractRedefinedException(const std::string& name, const std::string& element)
			: CAbstractException(element + " '" + name + "' redefined exception!") {
		}
	}

}