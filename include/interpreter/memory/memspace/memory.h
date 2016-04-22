#pragma once

#include <map>

#include "definitions/memoryDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

namespace interpreter {

	namespace core {
		namespace bootstrap {
			class CBootstrapStage1;
		}
	}

	namespace memory {

		namespace memspace {

			class CMemory {
			  private:
				std::vector<ptr(mem_component)> m_componentsMemory;

				std::vector<ptr(mem_port)> m_portsMemory;

				std::vector<ptr(mem_primitiveport)> m_primitivePortsMemory;

				std::vector<ptr(mem_service)> m_servicesMemory;

				std::vector<ptr(mem_primitiveservice)> m_primitiveServicesMemory;

				wptr(core::bootstrap::CBootstrapStage1) m_bootstrap1;

			  public:
				CMemory(ptr(core::bootstrap::CBootstrapStage1) bootstrap1 = nullptr);

				void setBootstrap1(ptr(core::bootstrap::CBootstrapStage1) bootstrap1);

				wptr(mem_component) newComponent();

				wptr(mem_int) newIntComponent(i64 value);

				wptr(mem_string) newStringComponent(const std::string& value);

				wptr(mem_bool) newBoolComponent(bool value);

				wptr(mem_port) newPrimitivePort(ptr(mem_component) owner, ptr(ast_port) port);

				wptr(mem_port) newPrimitivePort(ptr(mem_component) owner, const std::string& name, bool isCollection, type_visibility visibility, type_role role);

				wptr(mem_port) newComponentPort(ptr(mem_component) owner, ptr(ast_port) port);

				wptr(mem_port) newComponentPort(ptr(mem_component) port, type_visibility visibility, type_role role);

				wptr(mem_service) newPrimitiveService(ptr(mem_component) owner, const std::string& name,
				                                      std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)> callback
				                                      = std::function<ptr(objects::CGeneralPort)(const ptr(objects::CComponent)&)>());

				wptr(mem_service) newComponentService(ptr(mem_component) owner, ptr(ast_service) service);

				wptr(mem_service) newComponentService(ptr(mem_component) service, ptr(mem_service) specialized = nullptr);

				size_t getComponentsNumber() const;
			};

		}

	}
}
