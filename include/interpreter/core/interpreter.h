#pragma once

#include "types.h"
#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "interpreter/memory/memspace/descriptorTable.h"
#include "parser/parserWrapper.h"
#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "ast/semantic/syntaxDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"
#include "exceptions/runtime/unknownAstNodeTypeException.h"

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

			ptr(ParserWrapper) m_parser;
                        
                        ptr(core::CBootstrapStage1) m_bootstrap;
                        
                        ptr(memory::memspace::CDescriptorTable) m_descriptorTable;

			void checkMainContainer() const;

			void execProgram(ptr(ast_program) node);

			void execDescriptor(ptr(ast_descriptor) node);

			void exec(ptr(ast_node));

		  public:

			CInterpreter(ptr(ParserWrapper) parser = nullptr, ptr(CBootstrapStage1) bootstrap = nullptr, ptr(memory::memspace::CDescriptorTable) table = nullptr);

			void execService(const std::string& code);

			void run(ptr(ast_program) ast);
		};

	}
	/*! @}*/
}
/*! @}*/