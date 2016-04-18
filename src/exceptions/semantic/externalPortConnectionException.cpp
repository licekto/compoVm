#include "exceptions/semantic/externalPortConnectionException.h"

namespace exceptions {

	namespace semantic {

		CExternalPortConnectionException::CExternalPortConnectionException(const std::string& name)
			: CAbstractException("External port '" + name + "' cannot be connected from inside of component!") {
		}

		const char* CExternalPortConnectionException::what() const throw() {
			return m_msg.c_str();
		}
	}

}