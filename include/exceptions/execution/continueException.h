#pragma once

#include <string>
#include <memory>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace execution {

		class CContinueException : public CAbstractException {
		  public:
			CContinueException();

			virtual const char* what() const throw();
		};

	}

}