#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CUnknownPortTypeException : public CAbstractException {
		  public:

			CUnknownPortTypeException();

			virtual const char* what() const throw();
		};

	}

}