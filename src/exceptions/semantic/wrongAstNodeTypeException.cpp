#include "exceptions/semantic/wrongAstNodeTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongAstNodeTypeException::CWrongAstNodeTypeException(type_node expected, type_node actual)
			: CAbstractException("Wrong type of AST node. Actual: '" + types::typeName(expected) + "', expected: '" + types::typeName(actual) + "'.") {
		}


		const char* CWrongAstNodeTypeException::what() const throw() {
			return m_msg.c_str();
		}
	}

}