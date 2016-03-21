#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractRedefinitionException : public CAbstractException {
		  protected:
			std::string m_name;
			std::string m_element;
			std::string m_msg;

		  public:
			CAbstractRedefinitionException(std::string name, std::string element);

			virtual const char* what() const throw() = 0;
		};

	}

}