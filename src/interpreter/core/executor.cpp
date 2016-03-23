#include "interpreter/core/executor.h"

namespace interpreter {

	namespace core {

		CExecutor::CExecutor(ptr(ast_program) ast, ptr(ast::semantic::CGlobalDescriptorTable) table)
			: m_ast(ast), m_descriptorTable(table) {
		}

		void CExecutor::bootstrap() {
			if (!m_descriptorTable->symbolFound(COMPO_MAIN_COMPONENT_NAME)) {
				throw exceptions::runtime::CMainComponentMissingException();
			}

			ptr(ast_descriptor) container = cast(ast_descriptor)(m_descriptorTable->getSymbol(COMPO_MAIN_COMPONENT_NAME));

			if (!container->getServiceByName(COMPO_MAIN_SERVICE_NAME).use_count()) {
				throw exceptions::runtime::CMainServiceMissingException();
			}
		}

		void CExecutor::run() {

		}

	}

}