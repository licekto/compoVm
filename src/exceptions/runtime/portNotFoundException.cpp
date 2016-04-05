#include "exceptions/runtime/portNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CPortNotFoundException::CPortNotFoundException(const std::string& name)
			: CAbstractException("Port '" + name + "' not found!") {
		}

		const char* CPortNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}