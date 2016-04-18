#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CSelfPortNotCollectionException : public CAbstractException {
		  public:

			CSelfPortNotCollectionException();

			virtual const char* what() const throw();
		};

	}

}