#pragma once

#include <map>

#include "definitions/allDefinitions.h"

namespace interpreter {

	namespace memory {

		namespace objects {

			class CComponent : public std::enable_shared_from_this<CComponent> {
			  private:

				ptr(CComponent) m_defaultPort;

				ptr(CComponent) m_selfPort;

				ptr(CComponent) m_superPort;

				std::map<std::string, ptr(CComponent)> m_ports;

				std::map<std::string, ptr(CComponent)> m_services;

			  public:
                              
                              CComponent(ptr(CComponent) defaultPort = nullptr, ptr(CComponent) selfPort = nullptr, ptr(CComponent) superPort = nullptr);
                              
                              
			};

		}
	}
}