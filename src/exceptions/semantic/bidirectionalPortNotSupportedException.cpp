#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"

namespace exceptions {

	namespace semantic {

		CBidirectionalPortNotSupportedException::CBidirectionalPortNotSupportedException(const std::string& name)
			: CAbstractException("Bidirectional ports not supported. Violated with port '" + name + "'!") {
		}

		const char* CBidirectionalPortNotSupportedException::what() const throw() {
			return m_msg.c_str();
		}

	}

}