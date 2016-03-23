#include "interpreter/core/interpreter.h"

namespace interpreter {

	namespace core {

		CInterpreter::CInterpreter(ptr(ast_program) ast, ptr(ast::semantic::CGlobalDescriptorTable) table, ptr(CCoreModules) loader)
			: m_ast(ast), m_descriptorTable(table), m_kernelLoader(loader) {
		}
                
                void CInterpreter::checkMainContainer() const {
                        if (!m_descriptorTable->symbolFound(COMPO_MAIN_COMPONENT_NAME)) {
				throw exceptions::runtime::CMainComponentMissingException();
			}

			ptr(ast_descriptor) container = cast(ast_descriptor)(m_descriptorTable->getSymbol(COMPO_MAIN_COMPONENT_NAME));

			if (!container->getServiceByName(COMPO_MAIN_SERVICE_NAME).use_count()) {
				throw exceptions::runtime::CMainServiceMissingException();
			}
                }
                
		void CInterpreter::bootstrap() {
                        checkMainContainer();
                        
                        m_kernelLoader->loadModules();
		}

		void CInterpreter::run() {
                    bootstrap();
		}

	}

}