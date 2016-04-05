#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedDescriptorException : public CAbstractUndefinedException {
		  public:
			CUndefinedDescriptorException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}