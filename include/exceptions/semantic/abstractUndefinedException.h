#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractUndefinedException : public CAbstractException {
		  public:
			CAbstractUndefinedException(const std::string& name,const  std::string& element);

			virtual const char* what() const throw() = 0;
		};

	}

}