#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongNumberOfParametersException : public CAbstractException {
		  public:

			CWrongNumberOfParametersException(const std::string& serviceName, size_t number);

			virtual const char* what() const throw();
		};

	}

}