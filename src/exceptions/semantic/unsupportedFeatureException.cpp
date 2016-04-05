#include "exceptions/semantic/unsupportedFeatureException.h"

namespace exceptions {

	namespace semantic {

		CUnsupportedFeatureException::CUnsupportedFeatureException(const std::string& feature)
			: CAbstractException("Unsupported feature '" + feature + "' exception") {
		}

		const char* CUnsupportedFeatureException::what() const throw() {
			return m_msg.c_str();
		}

	}

}