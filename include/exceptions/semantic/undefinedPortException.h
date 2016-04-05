#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"
#include "definitions/allDefinitions.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedPortException : public CAbstractUndefinedException {
		  public:
			CUndefinedPortException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}