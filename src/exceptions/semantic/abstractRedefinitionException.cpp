
#include "exceptions/semantic/abstractRedefinitionException.h"

namespace exceptions {

	namespace semantic {

		CAbstractRedefinitionException::CAbstractRedefinitionException(std::string name)
			: m_name(name) {
		}

		std::string CAbstractRedefinitionException::getPartialMessage() const {
			std::string msg = m_name.c_str();
			msg += " redefinition exception!";

			return msg.c_str();
		}
	}

}