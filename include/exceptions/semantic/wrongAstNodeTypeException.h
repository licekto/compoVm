#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "definitions/astTypesDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CWrongAstNodeTypeException : public CAbstractException {
		  public:
			CWrongAstNodeTypeException(ast_nodetype actual, ast_nodetype expected);

			virtual const char* what() const throw();
		};

	}

}