#include "exceptions/runtime/wrongValueComponentPortException.h"

namespace exceptions {

	namespace runtime {

		CWrongValueComponentPortException::CWrongValueComponentPortException(const std::string& name)
			: CAbstractException("Wrong value component port with name: '" + name + "'!") {
		}

		const char* CWrongValueComponentPortException::what() const throw() {
			return m_msg.c_str();
		}

	}

}