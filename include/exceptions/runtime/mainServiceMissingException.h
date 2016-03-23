#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		class CMainServiceMissingException : public CAbstractException {
		  public:

			CMainServiceMissingException();

			virtual const char* what() const throw();
		};

	}

}