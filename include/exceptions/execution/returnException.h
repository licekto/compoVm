#pragma once

#include <string>
#include <memory>

#include "exceptions/abstractException.h"

namespace interpreter {
	namespace memory {
		namespace objects {
			class CGeneralPort;
		}
	}
}

namespace exceptions {

	namespace execution {

		class CReturnException : public CAbstractException {
			std::shared_ptr<interpreter::memory::objects::CGeneralPort> m_port;
		  public:
			CReturnException(std::shared_ptr<interpreter::memory::objects::CGeneralPort> port);

			virtual const char* what() const throw();

			std::shared_ptr<interpreter::memory::objects::CGeneralPort> getPort();
		};

	}

}