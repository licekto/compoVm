#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"
#include "astDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedDescriptorException : public CAbstractUndefinedException {
		  public:
			CUndefinedDescriptorException(std::string name);

			virtual const char* what() const throw();
		};

	}

}