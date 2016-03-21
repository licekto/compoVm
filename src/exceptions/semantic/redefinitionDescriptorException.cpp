#include "exceptions/semantic/redefinitionDescriptorException.h"

namespace exceptions {

	namespace semantic {

		CRedefinitionDescriptorException::CRedefinitionDescriptorException(std::string name)
			: CAbstractRedefinitionException(name, "Descriptor") {
		}

		const char* CRedefinitionDescriptorException::what() const throw() {
			return m_msg.c_str();
		}
	}

}