#pragma once

#include "definitions.h"
#include "interpreter/config.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"
#include "coreModules.h"

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
                        
                        ptr(CCoreModules) m_kernelLoader;

                        void checkMainContainer() const;
                        
			void bootstrap();

		  public:

			CInterpreter(ptr(ast_program) ast = nullptr, ptr(ast::semantic::CGlobalDescriptorTable) table = nullptr, ptr(CCoreModules) loader = nullptr);

			void run();
		};

	}
	/*! @}*/
}
/*! @}*/