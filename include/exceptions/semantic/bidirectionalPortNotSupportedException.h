#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CBidirectionalPortNotSupportedException : public CAbstractException {
		  public:
			CBidirectionalPortNotSupportedException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}