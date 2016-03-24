#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedSymbolException : public CAbstractUndefinedException {
		  public:
			CUndefinedSymbolException(std::string name);

			virtual const char* what() const throw();
		};

	}

}