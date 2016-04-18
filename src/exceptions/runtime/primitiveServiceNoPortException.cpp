#include "exceptions/runtime/primitiveServiceNoPortException.h"

namespace exceptions {

	namespace runtime {

		CPrimitiveServiceNoPortException::CPrimitiveServiceNoPortException()
			: CAbstractException("Primitive service does not have primitive port!") {
		}

		const char* CPrimitiveServiceNoPortException::what() const throw() {
			return m_msg.c_str();
		}

	}

}