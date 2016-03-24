#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		class CServiceNotCompiledException : public CAbstractException {
		  public:

			CServiceNotCompiledException(std::string name);

			virtual const char* what() const throw();
		};

	}

}