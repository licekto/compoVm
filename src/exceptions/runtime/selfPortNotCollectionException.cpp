#include "exceptions/runtime/selfPortNotCollectionException.h"

namespace exceptions {

	namespace runtime {

		CSelfPortNotCollectionException::CSelfPortNotCollectionException()
			: CAbstractException("Self port is not collection port!") {
		}

		const char* CSelfPortNotCollectionException::what() const throw() {
			return m_msg.c_str();
		}

	}

}