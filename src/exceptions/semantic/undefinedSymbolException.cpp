#include "exceptions/semantic/undefinedSymbolException.h"

namespace exceptions {

	namespace semantic {

		CUndefinedSymbolException::CUndefinedSymbolException(const std::string& name)
			: CAbstractUndefinedException(name, "Symbol") {
		}

		const char* CUndefinedSymbolException::what() const throw() {
			return m_msg.c_str();
		}
	}

}