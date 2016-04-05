#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace runtime {

		class CPortNotFoundException : public CAbstractException {
		  public:

			CPortNotFoundException(const std::string& name);

			virtual const char* what() const throw();
		};

	}

}