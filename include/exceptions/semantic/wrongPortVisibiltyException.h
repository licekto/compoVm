#pragma once

#include <string>
#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CWrongPortVisibilityException : public CAbstractException {
		  public:
			CWrongPortVisibilityException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}