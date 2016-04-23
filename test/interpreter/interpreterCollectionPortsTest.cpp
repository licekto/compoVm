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
    ptr(interpreter::memory::memspace::CMemory) memory = new_ptr(interpreter::memory::memspace::CMemory)();
    ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(new_ptr(interpreter::core::CCoreModules)(parser), nullptr, memory);
    memory->setBootstrap1(bootstrap1);
    ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);
    ptr(core_interpreter) interpreter = new_ptr(core_interpreter)(parser, bootstrap2, table);
    bootstrap1->setInterpreter(interpreter);
    return interpreter;
}

ptr(core_interpreter) interpreter = initInterpreter();

BOOST_AUTO_TEST_CASE(nonCollectionPortTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
        externally provides {\
            name : String;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
        service getName() {\
            return name;\
        }\
    }\
    descriptor A {\
        externally requires {\
            comp : B;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b1 b2 b3|\
            a := A.new();\
            b1 := B.new();\
            b1.setName(\"B1\");\
            b2 := B.new();\
            b2.setName(\"B2\");\
            b3 := B.new();\
            b3.setName(\"B3\");\
            connect comp@a to default@b1;\
            connect comp@a to default@b2;\
            connect comp@a to default@b3;\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(component->getPortByName("comp")->getConnectedPortsNumber(), 1);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(collectionPortBasicTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
    }\
    descriptor A {\
        externally requires {\
            comp[] : B;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b1 b2 b3 i res|\
            a := A.new();\
            i := connect comp@a to default@(B.new());\
            i := connect comp@a to default@(B.new());\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_int) component = cast(mem_int)(interpreter->run(program)->getOwner());
    BOOST_CHECK_EQUAL(component->getValue(), 1);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(sizeofTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
    }\
    descriptor A {\
        externally requires {\
            comp[] : B;\
        }\
        service connectedNumber() {\
            return sizeof(comp);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b1 b2 b3 i res|\
            a := A.new();\
            connect comp@a to default@(B.new());\
            connect comp@a to default@(B.new());\
            connect comp@a to default@(B.new());\
            connect comp@a to default@(B.new());\
            return a.connectedNumber();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_int) component = cast(mem_int)(interpreter->run(program)->getOwner());
    BOOST_CHECK_EQUAL(component->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(collectionPortTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
        externally provides {\
            name : String;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
        service getName() {\
            return name;\
        }\
    }\
    descriptor A {\
        externally requires {\
            comp[] : B;\
            indexes : String;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b0 b1 b2 i res|\
            a := A.new();\
            b0 := B.new();\
            b0.setName(\"B0\");\
            b1 := B.new();\
            b1.setName(\"B1\");\
            b2 := B.new();\
            b2.setName(\"B2\");\
            i := connect comp@a to default@b0;\
            res := i + \" \";\
            i := connect comp@a to default@b1;\
            res := res + i + \" \";\
            i := connect comp@a to default@b2;\
            res := res + i;\
            connect indexes@a to default@res;\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(component->getPortByName("comp")->getConnectedPortsNumber(), 3);
    BOOST_CHECK_EQUAL(component->getPortByName("indexes")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("indexes")->getConnectedPortAt(0)->getOwner())->getValue(), "0 1 2");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(collectionPortBasicInvocationTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
        service testB(a) {\
            return a + 1;\
        }\
    }\
    descriptor A {\
        externally requires {\
            comp[] : B;\
        }\
        service testA() {\
            return comp[0].testB(2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a res|\
            a := A.new();\
            connect comp@a to default@(B.new());\
            connect comp@a to default@(B.new());\
            return a.testA();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_int) component = cast(mem_int)(interpreter->run(program)->getOwner());
    BOOST_CHECK_EQUAL(component->getValue(), 3);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(collectionPortInvocationTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor B {\
        externally provides {\
            name : String;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
        service getName() {\
            return name;\
        }\
    }\
    descriptor A {\
        externally requires {\
            comp[] : B;\
            names : String;\
        }\
        service buildNames() {\
            comp[0].setName(\"B0\");\
            comp[1].setName(\"B1\");\
            comp[2].setName(\"B2\");\
        }\
        service concNames() {\
            names := comp[0].getName() + \" \" + comp[1].getName() + \" \" + comp[2].getName();\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b0 b1 b2 i res|\
            a := A.new();\
            b0 := B.new();\
            b1 := B.new();\
            b2 := B.new();\
            connect comp@a to default@b0;\
            connect comp@a to default@b1;\
            connect comp@a to default@b2;\
            a.buildNames();\
            a.concNames();\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(component->getPortByName("comp")->getConnectedPortsNumber(), 3);
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("comp")->getConnectedPortAt(0)->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "B0");
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("comp")->getConnectedPortAt(1)->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "B1");
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("comp")->getConnectedPortAt(2)->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "B2");
    BOOST_CHECK_EQUAL(component->getPortByName("names")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("names")->getConnectedPortAt(0)->getOwner())->getValue(), "B0 B1 B2");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
