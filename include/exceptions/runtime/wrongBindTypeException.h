#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongBindTypeException : public CAbstractException {
		  public:

			CWrongBindTypeException(const std::string& bindType);

			virtual const char* what() const throw();
		};

	}

}