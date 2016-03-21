#pragma once

#include <string>

#include "exceptions/abstractException.h"

namespace exceptions {

	namespace semantic {

		class CAbstractUndefinedException : public CAbstractException {
		  protected:
			std::string m_name;
			std::string m_element;
			std::string m_msg;

		  public:
			CAbstractUndefinedException(std::string name, std::string element);

			virtual const char* what() const throw() = 0;
		};

	}

}