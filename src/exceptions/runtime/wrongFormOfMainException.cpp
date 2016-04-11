#include "exceptions/runtime/wrongFormOfMainException.h"
#include "interpreter/config.h"

namespace exceptions {

	namespace runtime {

		CWrongFormOfMainException::CWrongFormOfMainException()
			: CAbstractException("Wrong form of main component ('" + 
                            std::string(COMPO_MAIN_COMPONENT_NAME) + "') or main service ('" + std::string(COMPO_MAIN_SERVICE_NAME) + "')!") {
		}

		const char* CWrongFormOfMainException::what() const throw() {
			return m_msg.c_str();
		}

	}

}