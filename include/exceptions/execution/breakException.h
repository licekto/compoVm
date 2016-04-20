#pragma once

#include <string>
#include <memory>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace execution {

		class CBreakException : public CAbstractException {
		  public:
			CBreakException();

			virtual const char* what() const throw();
		};

	}

}