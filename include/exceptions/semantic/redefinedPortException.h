#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinedException.h"
#include "astDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedPortException : public CAbstractRedefinedException {
		  public:
			CRedefinedPortException(std::string name);

			virtual const char* what() const throw();
		};

	}

}