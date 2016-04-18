#include "exceptions/runtime/variableNotFoundException.h"

namespace exceptions {

	namespace runtime {

		CVariableNotFoundException::CVariableNotFoundException(const std::string& name)
			: CAbstractException("Variable '" + name + "' not found!") {
		}

		const char* CVariableNotFoundException::what() const throw() {
			return m_msg.c_str();
		}

	}

}