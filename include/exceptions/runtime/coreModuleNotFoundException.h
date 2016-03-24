#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CCoreModuleNotFoundException : public CAbstractException {
		  public:

			CCoreModuleNotFoundException(std::string module);

			virtual const char* what() const throw();
		};

	}

}