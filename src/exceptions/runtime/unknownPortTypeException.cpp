#include "exceptions/runtime/unknownPortTypeException.h"

namespace exceptions {

	namespace runtime {

		CUnknownPortTypeException::CUnknownPortTypeException()
			: CAbstractException("Unknown port type!") {
		}

		const char* CUnknownPortTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}