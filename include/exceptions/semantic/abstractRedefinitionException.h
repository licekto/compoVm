#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractRedefinitionException : public CAbstractException {
		  protected:
			std::string m_name;

		  public:
			CAbstractRedefinitionException(std::string name);

			virtual const char* what() const throw() = 0;

			std::string getPartialMessage() const;
		};

	}

}