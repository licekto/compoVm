#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CBidirectionalPortNotSupportedException : public CAbstractException {
		  public:
			CBidirectionalPortNotSupportedException(std::string name);

			virtual const char* what() const throw();
		};

	}

}