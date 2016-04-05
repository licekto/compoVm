#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CServiceNotCompiledException : public CAbstractException {
		  public:

			CServiceNotCompiledException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}