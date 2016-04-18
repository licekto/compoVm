#pragma once

#include <string>

#include "exceptions/abstractException.h"
#include "definitions/typesDefinitions.h"

namespace exceptions {

	namespace runtime {

		class CWrongServiceInvocationParameterTypeException : public CAbstractException {
		  public:

			CWrongServiceInvocationParameterTypeException(type_node node);

			virtual const char* what() const throw();
		};

	}

}