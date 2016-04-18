#include "exceptions/runtime/wrongServiceTypeInArchitectureException.h"

namespace exceptions {

	namespace runtime {

		CWrongServiceTypeInArchitectureException::CWrongServiceTypeInArchitectureException()
			: CAbstractException("Wrong service type in \"architecture\" definition!") {
		}

		const char* CWrongServiceTypeInArchitectureException::what() const throw() {
			return m_msg.c_str();
		}

	}

}