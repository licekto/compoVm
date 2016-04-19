#include "exceptions/semantic/wrongPortVisibiltyException.h"

namespace exceptions {

	namespace semantic {

		CWrongPortVisibilityException::CWrongPortVisibilityException(const std::string& name)
			: CAbstractException("External port '" + name + "' cannot be connected from inside of component!") {
		}

		const char* CWrongPortVisibilityException::what() const throw() {
			return m_msg.c_str();
		}
	}

}