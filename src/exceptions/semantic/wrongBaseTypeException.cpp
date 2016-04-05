#include "exceptions/semantic/wrongBaseTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongBaseTypeException::CWrongBaseTypeException(type_node expected, type_node actual)
			: CAbstractException("Extension of wrong base element. Actual: '" + types::typeName(expected) + "', expected: '" + types::typeName(actual) + "'.") {
		}


		const char* CWrongBaseTypeException::what() const throw() {
			return m_msg.c_str();
		}
	}

}