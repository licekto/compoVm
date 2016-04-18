#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CUnknownValueComponentTypeException : public CAbstractException {
		  public:

			CUnknownValueComponentTypeException();

			virtual const char* what() const throw();
		};

	}

}