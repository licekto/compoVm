
#include "exceptions/semantic/abstractRedefinitionException.h"

namespace exceptions {

	namespace semantic {

		CAbstractRedefinitionException::CAbstractRedefinitionException(std::string name, std::string element)
			: m_name(name), m_element(element), m_msg("") {
			m_msg = m_element.c_str();
			m_msg += " '";
			m_msg += m_name.c_str();
			m_msg += "' undefined exception!";
		}
	}

}