#include "exceptions/semantic/wrongBaseTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongBaseTypeException::CWrongBaseTypeException(ast_type expected, ast_type actual)
			: CAbstractException(),
			  m_expected(expected),
			  m_actual(actual) {
		}


		const char* CWrongBaseTypeException::what() const throw() {
			std::string msg = "Extension of wrong base element. Actual: '";
			msg += ast::nodes::types::typeName(m_expected);
			msg += "', expected: '";
			msg += ast::nodes::types::typeName(m_actual);
			msg += "'.";

			return msg.c_str();
		}
	}

}