#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongPortTypeException : public CAbstractException {
		  public:

			CWrongPortTypeException(const std::string& type, const std::string& service);

			virtual const char* what() const throw();
		};

	}

}