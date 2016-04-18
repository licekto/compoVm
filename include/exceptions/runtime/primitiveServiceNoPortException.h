#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CPrimitiveServiceNoPortException : public CAbstractException {
		  public:

			CPrimitiveServiceNoPortException();

			virtual const char* what() const throw();
		};

	}

}