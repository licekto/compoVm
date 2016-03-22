#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CUnsupportedFeatureException : public CAbstractException {
		  public:
			CUnsupportedFeatureException(std::string feature);

			virtual const char* what() const throw();
		};

	}

}