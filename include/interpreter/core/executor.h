#pragma once

#include "definitions.h"
#include "interpreter/config.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"

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
		class CExecutor {
		  private:

			ptr(ast_program) m_ast;

			ptr(ast::semantic::CGlobalDescriptorTable) m_descriptorTable;

			void bootstrap();

		  public:

			CExecutor(ptr(ast_program) ast, ptr(ast::semantic::CGlobalDescriptorTable) table);

			void run();
		};

	}
	/*! @}*/
}
/*! @}*/