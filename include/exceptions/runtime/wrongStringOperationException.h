#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongStringOperationException : public CAbstractException {
		  public:

			CWrongStringOperationException();

			virtual const char* what() const throw();
		};

	}

}