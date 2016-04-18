#include "exceptions/runtime/unknownValueComponentTypeException.h"

namespace exceptions {

	namespace runtime {

		CUnknownValueComponentTypeException::CUnknownValueComponentTypeException()
			: CAbstractException("Unknown value component type!") {
		}

		const char* CUnknownValueComponentTypeException::what() const throw() {
			return m_msg.c_str();
		}

	}

}