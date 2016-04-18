#include "exceptions/runtime/wrongServiceInvocationParameterTypeException.h"

namespace exceptions {

	namespace runtime {

		CWrongServiceInvocationParameterTypeException::CWrongServiceInvocationParameterTypeException(type_node node)
			: CAbstractException("Wrong service invocation parameter type: '" + types::typeName(node) + "'!") {
		}

		const char* CWrongServiceInvocationParameterTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}