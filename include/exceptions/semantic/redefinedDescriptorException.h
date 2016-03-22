#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinedException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedDescriptorException : public CAbstractRedefinedException {
		  public:

			CRedefinedDescriptorException(std::string name);

			virtual const char* what() const throw();
		};

	}

}