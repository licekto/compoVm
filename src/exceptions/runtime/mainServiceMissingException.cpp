#include "exceptions/runtime/mainServiceMissingException.h"

namespace exceptions {

	namespace runtime {

		CMainServiceMissingException::CMainServiceMissingException()
			: CAbstractException(std::string(COMPO_MAIN_SERVICE_NAME) + " service missing!") {
		}

		const char* CMainServiceMissingException::what() const throw() {
			return m_msg.c_str();
		}

	}

}