#include "exceptions/semantic/wrongBaseTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongBaseTypeException::CWrongBaseTypeException(ast_nodetype expected, ast_nodetype actual)
			: CAbstractException("Extension of wrong base element. Actual: '" + ast::nodes::types::typeName(expected) + "', expected: '" + ast::nodes::types::typeName(actual) + "'.") {
		}


		const char* CWrongBaseTypeException::what() const throw() {
			return m_msg.c_str();
		}
	}

}