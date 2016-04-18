#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CVariableNotFoundException : public CAbstractException {
		  public:

			CVariableNotFoundException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}