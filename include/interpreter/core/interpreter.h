#pragma once

#include <stack>

#include "types.h"
#include "interpreter/core/bootstrap/bootstrapStage2.h"
#include "interpreter/memory/memspace/descriptorTable.h"
#include "parser/parserWrapper.h"
#include "definitions/allDefinitions.h"
#include "interpreter/config.h"
#include "ast/semantic/syntaxDescriptorsTable.h"
#include "exceptions/runtime/mainComponentMissingException.h"
#include "exceptions/runtime/mainServiceMissingException.h"
#include "exceptions/runtime/unknownAstNodeTypeException.h"
#include "exceptions/runtime/wrongFormOfMainException.h"
#include "exceptions/execution/returnException.h"
#include "exceptions/runtime/unknownOperatorTypeException.h"
#include "exceptions/runtime/wrongServiceInvocationParameterTypeException.h"
#include "exceptions/semantic/wrongPortVisibiltyException.h"
#include "variablesTable.h"
#include "context.h"

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

			ptr(bootstrap::CBootstrapStage2) m_bootstrap;

			ptr(memory::memspace::CDescriptorTable) m_descriptorTable;
                        
                        std::stack<ptr(CContext)> m_serviceContextStack;

			ptr(mem_port) execProgram(ptr(ast_program) node);

			void execDescriptor(ptr(ast_descriptor) node);
                        
                        void execCompound(ptr(ast_compound) node);
                        
                        void execAssignment(ptr(ast_assignment) node);
                        
                        ptr(mem_port) execArithmeticOp(ptr(ast_binary) expr, type_operator op);
                        
                        ptr(mem_port) execLogicalOp(ptr(ast_binary) expr, type_operator op);
                        
                        ptr(mem_port) execRelationalOp(ptr(ast_binary) expr, type_operator op);
                        
                        ptr(mem_port) execServiceInvocation(ptr(ast_serviceinvocation) node);

                        ptr(mem_port) execConnection(ptr(ast_connection) node);
                        
                        ptr(mem_port) execDisconnection(ptr(ast_disconnection) node);
                        
			ptr(mem_port) exec(ptr(ast_node));

		  public:

			CInterpreter(ptr(ParserWrapper) parser = nullptr,
                                     ptr(bootstrap::CBootstrapStage2) bootstrap = nullptr,
                                     ptr(memory::memspace::CDescriptorTable) table = nullptr);

			ptr(mem_port) execServiceCode(const std::string& code, ptr(CContext) context = nullptr);
                        
                        ptr(mem_port) execService(const std::string& receiver, const std::string& selector);
                        
			ptr(mem_port) run(ptr(ast_program) ast);
		};

	}
	/*! @}*/
}
/*! @}*/