#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CWrongAstNodeTypeException : public CAbstractException {
		  private:
			ast_type m_expected;
			ast_type m_actual;

		  public:
			CWrongAstNodeTypeException(ast_type actual, ast_type expected);

			virtual const char* what() const throw();
		};

	}

}