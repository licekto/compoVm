#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CWrongValueComponentPortException : public CAbstractException {
		  public:

			CWrongValueComponentPortException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}