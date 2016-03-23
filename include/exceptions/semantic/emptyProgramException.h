#pragma once

#include <string>
#include "exceptions/abstractException.h"
#include "astDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CEmptyProgramException : public CAbstractException {
		  public:
			CEmptyProgramException();

			virtual const char* what() const throw();
		};

	}

}