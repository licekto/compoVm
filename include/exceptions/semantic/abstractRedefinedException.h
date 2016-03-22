#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractRedefinedException : public CAbstractException {
		  public:
			CAbstractRedefinedException(std::string name, std::string element);

			virtual const char* what() const throw() = 0;
		};

	}

}