#pragma once

#include <map>
#include <functional>
#include <cstdlib>

#include "definitions/memoryObjectsDefinitions.h"

#include "types.h"
#include "interpreter/config.h"
#include "interpreter/core/coreModules.h"
#include "bootstrapStage1.h"
#include "exceptions/runtime/selfPortNotCollectionException.h"
#include "exceptions/runtime/wrongServiceTypeInArchitectureException.h"
#include "exceptions/runtime/wrongBindTypeException.h"
#include "exceptions/semantic/wrongPortVisibiltyException.h"

namespace interpreter {

	namespace core {

		namespace bootstrap {

			class CBootstrapStage2 {
			  private:
				ptr(CBootstrapStage1) m_bootstrapStage1;

				void addPorts(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

				void addServices(ptr(mem_component) component, ptr(ast_descriptor) descriptor);

				ptr(mem_component) bootstrapRootComponent(ptr(mem_component) owner);

				ptr(mem_component) buildPortFromDescription(ptr(mem_component) description, ptr(mem_component) owner);

				ptr(mem_component) cloneInterface(ptr(mem_component) interface, ptr(mem_component) portOwner);

				ptr(mem_component) cloneSignature(ptr(mem_component) signature, ptr(mem_component) owner);

				ptr(mem_component) cloneService(ptr(mem_component) service, ptr(mem_component) owner);

				ptr(mem_component) bootstrapPrologue(const std::string& coreDescriptorName);

				void bootstrapEpilogue(ptr(mem_component) component);

			  public:
				CBootstrapStage2(ptr(CBootstrapStage1) stage1 = nullptr);

				void checkPortSemantics(ptr(mem_port) port, ptr(mem_component) owner);

				ptr(mem_port) getIntComponent(i64 value);

				ptr(mem_port) getStringComponent(const std::string& value);

				ptr(mem_port) getBoolComponent(bool value);

				ptr(mem_component) bootstrapSystemComponent();
                                
                                ptr(mem_component) bootstrapServiceDescriptorComponent();
                                
                                ptr(mem_component) bootstrapPortDescriptionComponent();

				ptr(mem_component) bootstrapDescriptorComponent(ptr(ast_descriptor) descriptor);
			};

		}

	}
}