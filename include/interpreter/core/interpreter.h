#pragma once

#include "definitions/allDefinitions.h"
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

			ptr(ParserWrapper) m_parser;

			ptr(CCoreModules) m_coreModules;

			void checkMainContainer() const;

			void execProgram(ptr(ast_program) node);

			void execDescriptor(ptr(ast_descriptor) node);

			void exec(ptr(ast_node));

			void loadCoreToDescriptorTable();



		  public:

			CInterpreter(ptr(ParserWrapper) parser = nullptr,
			             ptr(CCoreModules) modules = nullptr);

                        void execService(const std::string& code);
                        
			void run(ptr(ast_program) ast);

			ptr(memory::objects::CComponent) createComponentFromDescriptor(ptr(ast_descriptor) descriptor);
		};

	}
	/*! @}*/
}
/*! @}*/