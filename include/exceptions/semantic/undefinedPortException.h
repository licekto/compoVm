#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"
#include "astDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedPortException : public CAbstractUndefinedException {
		  public:
			CUndefinedPortException(std::string name);

			virtual const char* what() const throw();
		};

	}

}