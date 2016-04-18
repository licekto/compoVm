#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "definitions/typesDefinitions.h"

namespace exceptions {

	namespace runtime {

		class CWrongServiceTypeInArchitectureException : public CAbstractException {
		  public:

			CWrongServiceTypeInArchitectureException();

			virtual const char* what() const throw();
		};

	}

}