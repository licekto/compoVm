#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "logger/logger.h"

#include "definitions/allDefinitions.h"
#include "definitions/interpreterDefinitions.h"
#include "testDefinitions.h"
#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "ast/visitor/semanticCheckVisitor.h"
#include "ast/semantic/syntaxDescriptorsTable.h"
#include "exceptions/semantic/emptyProgramException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedInterfaceException.h"
#include "exceptions/semantic/redefinedDescriptorException.h"
#include "exceptions/semantic/redefinedInterfaceException.h"
#include "exceptions/semantic/wrongBaseTypeException.h"
#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"
#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "exceptions/semantic/wrongPortVisibiltyException.h"
#include "ast/visitor/printVisitor.h"

BOOST_AUTO_TEST_SUITE(interpreterCollectionPortsTest)

ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(interpreter::memory::memspace::CDescriptorTable) table = new_ptr(interpreter::memory::memspace::CDescriptorTable)();

ptr(core_interpreter) initInterpreter() {
    ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(new_ptr(interpreter::core::CCoreModules)(parser));
    ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);
    ptr(core_interpreter) interpreter = new_ptr(core_interpreter)(parser, bootstrap2, table);
    bootstrap1->setInterpreter(interpreter);
    return interpreter;
}

BOOST_AUTO_TEST_CASE(basicTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
        externally provides {\
            a : { add(a, b); };\
        }\
        service add(a, b) {\
            return a + b;\
        }\
    }\
    descriptor A {\
        externally requires {\
            arithmetics[] : B;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a|\
            a := A.new();\
            connect arithmetics@a to default@(B.new());\
            connect arithmetics@a to default@(B.new());\
            connect arithmetics@a to default@(B.new());\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    interpreter->run(program);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
