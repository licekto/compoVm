#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractUndefinedException : public CAbstractException {
		  public:
			CAbstractUndefinedException(std::string name, std::string element);

			virtual const char* what() const throw() = 0;
		};

	}

}