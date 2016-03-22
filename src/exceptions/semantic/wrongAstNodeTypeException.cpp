#include "exceptions/semantic/wrongAstNodeTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongAstNodeTypeException::CWrongAstNodeTypeException(ast_type expected, ast_type actual)
			: CAbstractException(),
			  m_expected(expected),
			  m_actual(actual) {
		}


		const char* CWrongAstNodeTypeException::what() const throw() {
			std::string msg = "Wrong type of AST node. Actual: '";
			msg += ast::nodes::types::typeName(m_expected);
			msg += "', expected: '";
			msg += ast::nodes::types::typeName(m_actual);
			msg += "'.";

			return msg.c_str();
		}
	}

}