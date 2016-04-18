#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CUnknownOperatorTypeException : public CAbstractException {
		  public:

			CUnknownOperatorTypeException();

			virtual const char* what() const throw();
		};

	}

}