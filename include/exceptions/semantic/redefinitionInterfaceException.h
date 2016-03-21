#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "exceptions/semantic/abstractRedefinitionException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CRedefinitionInterfaceException : public CAbstractRedefinitionException {
		  public:

			CRedefinitionInterfaceException(std::string name);

			virtual const char* what() const throw();
		};

	}

}