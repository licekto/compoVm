#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CUnknownAstNodeTypeException : public CAbstractException {
		  public:

			CUnknownAstNodeTypeException(const std::string& type);

			virtual const char* what() const throw();
		};

	}

}