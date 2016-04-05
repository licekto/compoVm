#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinedException.h"

namespace exceptions {

	namespace semantic {

		class CRedefinedDescriptorException : public CAbstractRedefinedException {
		  public:
			CRedefinedDescriptorException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}