#pragma once

#include <string>
#include "exceptions/semantic/abstractUndefinedException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CUndefinedSymbolException : public CAbstractUndefinedException {
		  public:
                        
                        CUndefinedSymbolException(std::string name);
			
                        virtual const char* what() const throw();
		};

	}

}