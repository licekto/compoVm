#include "exceptions/abstractException.h"

namespace exceptions {

	CAbstractException::CAbstractException(const std::string& msg)
		: m_msg(msg) {
	}

}