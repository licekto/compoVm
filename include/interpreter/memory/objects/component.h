#pragma once

#include <map>

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent : public std::enable_shared_from_this<CComponent> {
			  private:

				ptr(CComponent) m_default;

				ptr(CComponent) m_self;

				ptr(CComponent) m_super;

				std::map<std::string, ptr(CComponent)> m_ports;

				std::map<std::string, ptr(CComponent)> m_services;

			  public:
			};

		}
	}
}