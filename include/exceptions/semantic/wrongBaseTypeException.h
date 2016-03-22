#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CWrongBaseTypeException : public CAbstractException {
		  public:
			CWrongBaseTypeException(ast_nodetype actual, ast_nodetype expected);

			virtual const char* what() const throw();
		};

	}

}