#pragma once

#include <string>
#include "exceptions/semantic/abstractRedefinitionException.h"
#include "definitions.h"

namespace exceptions {

	namespace semantic {

		class CRedefinitionDescriptorException : public CAbstractRedefinitionException {
		  public:
                        
                        CRedefinitionDescriptorException(std::string name);
			
                        virtual const char* what() const throw();
		};

	}

}