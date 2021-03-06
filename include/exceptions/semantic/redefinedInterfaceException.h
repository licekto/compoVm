#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinedException.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedInterfaceException : public CAbstractRedefinedException {
		  public:
			CRedefinedInterfaceException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}