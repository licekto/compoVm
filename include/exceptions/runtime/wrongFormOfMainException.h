#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongFormOfMainException : public CAbstractException {
		  public:

			CWrongFormOfMainException();

			virtual const char* what() const throw();
		};

	}

}