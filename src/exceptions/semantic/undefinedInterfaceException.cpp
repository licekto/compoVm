#include "exceptions/semantic/undefinedInterfaceException.h"

namespace exceptions {

	namespace semantic {

		CUndefinedInterfaceException::CUndefinedInterfaceException(const std::string& name)
			: CAbstractUndefinedException(name, "Interface") {
		}

		const char* CUndefinedInterfaceException::what() const throw() {
			return m_msg.c_str();
		}
	}

}