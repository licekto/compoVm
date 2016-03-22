#include "exceptions/semantic/wrongAstNodeTypeException.h"

namespace exceptions {

	namespace semantic {

		CWrongAstNodeTypeException::CWrongAstNodeTypeException(ast_nodetype expected, ast_nodetype actual)
			: CAbstractException("Wrong type of AST node. Actual: '" + ast::nodes::types::typeName(expected) + "', expected: '" + ast::nodes::types::typeName(actual) + "'.") {
		}


		const char* CWrongAstNodeTypeException::what() const throw() {
			return m_msg.c_str();
		}
	}

}