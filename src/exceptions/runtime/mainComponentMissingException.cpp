#include "exceptions/runtime/mainComponentMissingException.h"

namespace exceptions {

	namespace runtime {

		CMainComponentMissingException::CMainComponentMissingException()
			: CAbstractException(std::string(COMPO_MAIN_COMPONENT_NAME) + " component missing!") {
		}

		const char* CMainComponentMissingException::what() const throw() {
			return m_msg.c_str();
		}

	}

}