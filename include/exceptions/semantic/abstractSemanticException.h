#pragma once

#include <exception>

namespace exceptions {

	namespace semantic {

		class CAbstractSemanticException : public CAbstractException {
			virtual const char* what() const throw() = 0;
		};

	}

}