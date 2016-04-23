#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongParametersException : public CAbstractException {
		  public:

			CWrongParametersException(const std::string& msg);

			virtual const char* what() const throw();
		};

	}

}