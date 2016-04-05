#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		CAbstractUndefinedException::CAbstractUndefinedException(const std::string& name, const std::string& element)
			: CAbstractException(element + " '" + name + "' undefined exception!") {
		}
	}

}