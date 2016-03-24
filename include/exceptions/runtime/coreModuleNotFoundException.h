#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		class CCoreModuleNotFoundException : public CAbstractException {
		  public:

			CCoreModuleNotFoundException(std::string module);

			virtual const char* what() const throw();
		};

	}

}