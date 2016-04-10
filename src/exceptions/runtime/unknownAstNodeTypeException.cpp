#include "exceptions/runtime/unknownAstNodeTypeException.h"

namespace exceptions {

	namespace runtime {

		CUnknownAstNodeTypeException::CUnknownAstNodeTypeException(const std::string& type)
			: CAbstractException("Unknown AST node type '" + type + "'!") {
		}

		const char* CUnknownAstNodeTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}