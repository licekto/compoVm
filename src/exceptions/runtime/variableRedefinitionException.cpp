#include "exceptions/runtime/variableRedefinitionException.h"

namespace exceptions {

	namespace runtime {

		CVariableRedefinitionException::CVariableRedefinitionException(const std::string& name)
			: CAbstractException("Variable '" + name + "' redefined!") {
		}

		const char* CVariableRedefinitionException::what() const throw() {
			return m_msg.c_str();
		}

	}

}