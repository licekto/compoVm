#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "definitions/typesDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CWrongBaseTypeException : public CAbstractException {
		  public:
			CWrongBaseTypeException(type_node actual, type_node expected);

			virtual const char* what() const throw();
		};

	}

}