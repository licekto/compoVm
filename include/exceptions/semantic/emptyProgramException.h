#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CEmptyProgramException : public CAbstractException {
		  public:
			virtual const char* what() const throw();
		};

	}

}