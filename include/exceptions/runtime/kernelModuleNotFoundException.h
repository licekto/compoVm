#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		class CKernelModuleNotFoundException : public CAbstractException {
		  public:

			CKernelModuleNotFoundException(std::string module);

			virtual const char* what() const throw();
		};

	}

}