#pragma once

#include <exception>
#include <string>

namespace exceptions {

	class CAbstractException : public std::exception {
	  protected:
		std::string m_msg;
	  public:
		CAbstractException(std::string msg);

		virtual const char* what() const throw() = 0;
	};

}