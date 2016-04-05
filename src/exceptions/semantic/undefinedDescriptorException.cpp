#include "exceptions/semantic/undefinedDescriptorException.h"

namespace exceptions {

	namespace semantic {

		CUndefinedDescriptorException::CUndefinedDescriptorException(const std::string& name)
			: CAbstractUndefinedException(name, "Descriptor") {
		}

		const char* CUndefinedDescriptorException::what() const throw() {
			return m_msg.c_str();
		}
	}

}