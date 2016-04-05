#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinedException.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedPortException : public CAbstractRedefinedException {
		  public:
			CRedefinedPortException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}