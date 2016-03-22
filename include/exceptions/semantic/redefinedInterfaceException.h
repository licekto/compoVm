#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "exceptions/semantic/abstractRedefinedException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedInterfaceException : public CAbstractRedefinedException {
		  public:

			CRedefinedInterfaceException(std::string name);

			virtual const char* what() const throw();
		};

	}

}