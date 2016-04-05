#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedInterfaceException : public CAbstractUndefinedException {
		  public:
			CUndefinedInterfaceException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}