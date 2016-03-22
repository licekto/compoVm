#include "exceptions/semantic/redefinedDescriptorException.h"

namespace exceptions {

	namespace semantic {

		CRedefinedDescriptorException::CRedefinedDescriptorException(std::string name)
			: CAbstractRedefinedException(name, "Descriptor") {
		}

		const char* CRedefinedDescriptorException::what() const throw() {
			return m_msg.c_str();
		}
	}

}