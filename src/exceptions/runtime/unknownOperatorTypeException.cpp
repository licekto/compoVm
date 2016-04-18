#include "exceptions/runtime/unknownOperatorTypeException.h"

namespace exceptions {

	namespace runtime {

		CUnknownOperatorTypeException::CUnknownOperatorTypeException()
			: CAbstractException("Unknown operator type!") {
		}

		const char* CUnknownOperatorTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}