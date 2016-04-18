#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CVariableRedefinitionException : public CAbstractException {
		  public:

			CVariableRedefinitionException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}