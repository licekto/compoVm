#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractUndefinedException : public CAbstractException {
                protected:
                    std::string m_name;
                    
                public:
                    CAbstractUndefinedException(std::string name);
                    
                    virtual const char* what() const throw() = 0;
                    
                    std::string getPartialMessage() const;
		};

	}

}