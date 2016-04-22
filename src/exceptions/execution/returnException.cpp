#include "exceptions/execution/returnException.h"

namespace exceptions {

	namespace execution {

		CReturnException::CReturnException(std::shared_ptr<interpreter::memory::objects::CGeneralPort> port)
			: CAbstractException("Return exception."), m_port(port) {
		}

		const char* CReturnException::what() const throw() {
			return m_msg.c_str();
		}

		std::shared_ptr<interpreter::memory::objects::CGeneralPort> CReturnException::getPort() {
			return m_port;
		}

	}

}