#pragma once

#include <string>
#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CExternalPortConnectionException : public CAbstractException {
		  public:
			CExternalPortConnectionException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}