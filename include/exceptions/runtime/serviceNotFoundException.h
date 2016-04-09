#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CServiceNotFoundException : public CAbstractException {
		  public:

			CServiceNotFoundException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}