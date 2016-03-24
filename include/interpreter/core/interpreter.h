#pragma once

#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"
#include "coreModules.h"
#include "interpreter/memory/manager/manager.h"

/**
 *  \addtogroup interpreter
 *  @{
 */

/**
 * interpreter Namespace
 */
namespace interpreter {

	/**
	*  \addtogroup core
	*  @{
	*/

	/**
	 * core Namespace
	 */
	namespace core {
		/**
		 * \class CExecutor
		 * \brief AST executor class.
		 */
		class CInterpreter {
		  private:

			ptr(ast_program) m_ast;

			ptr(ast::semantic::CGlobalDescriptorTable) m_descriptorTable;

			ptr(CCoreModules) m_coreModules;
                        
                        ptr(memory::manager::CManager) m_memory;

			void checkMainContainer() const;

		  public:

			CInterpreter(ptr(ast_program) ast = nullptr,
                                     ptr(ast::semantic::CGlobalDescriptorTable) table = nullptr,
                                     ptr(CCoreModules) loader = nullptr,
                                     ptr(memory::manager::CManager) manager = nullptr);

			void run();
		};

	}
	/*! @}*/
}
/*! @}*/