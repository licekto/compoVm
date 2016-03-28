#pragma once

#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"
#include "coreModules.h"
#include "interpreter/core/bootstrap.h"

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

			ptr(core::CBootstrap) m_memory;

			ptr(CCoreModules) m_coreModules;

			void checkMainContainer() const;

			void execProgram(ptr(ast_program) node);

			void execDescriptor(ptr(ast_descriptor) node);

			void exec(ptr(ast_node));

			void loadCoreToDescriptorTable();



		  public:

			CInterpreter(ptr(ast::semantic::CGlobalDescriptorTable) table = nullptr,
			             ptr(core::CBootstrap) manager = nullptr,
			             ptr(CCoreModules) modules = nullptr);

			void run(ptr(ast_program) ast);

			ptr(memory::objects::CComponent) createComponentFromDescriptor(ptr(ast_descriptor) descriptor);
		};

	}
	/*! @}*/
}
/*! @}*/