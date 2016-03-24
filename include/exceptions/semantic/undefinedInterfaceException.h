#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"
#include "definitions/allDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedInterfaceException : public CAbstractUndefinedException {
		  public:
			CUndefinedInterfaceException(std::string name);

			virtual const char* what() const throw();
		};

	}

}