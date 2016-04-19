#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CMemoryNotFoundException : public CAbstractException {
		  public:

			CMemoryNotFoundException();

			virtual const char* what() const throw();
		};

	}

}