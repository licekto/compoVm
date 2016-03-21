#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {

		CAbstractUndefinedException::CAbstractUndefinedException(std::string name, std::string element)
			: m_name(name), m_element(element), m_msg("") {
			m_msg = m_element.c_str();
			m_msg += " '";
			m_msg += m_name.c_str();
			m_msg += "' undefined exception!";
		}
	}

}