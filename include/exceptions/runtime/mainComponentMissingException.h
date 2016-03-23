#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		class CMainComponentMissingException : public CAbstractException {
		  public:

			CMainComponentMissingException();

			virtual const char* what() const throw();
		};

	}

}