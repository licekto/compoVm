#include "exceptions/semantic/abstractUndefinedException.h"

namespace exceptions {

	namespace semantic {
            
                CAbstractUndefinedException::CAbstractUndefinedException(std::string name)
                        : m_name(name) {
                }
            
		std::string CAbstractUndefinedException::getPartialMessage() const {
                        std::string msg = m_name.c_str();
                        msg += " undefined exception!";

			return msg.c_str();
		}
	}

}