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

BOOST_AUTO_TEST_SUITE(interpreterSimplePortsTest)

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
   "descriptor CompoContainer {\
        service main() {\
            |a|\
            a := 1;\
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

BOOST_AUTO_TEST_CASE(basicInstantiationTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
    }\
    descriptor B {\
    }\
    descriptor C {\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
        }\
        internally provides {\
            b : B;\
        }\
        externally requires {\
            c : C;\
        }\
        externally provides {\
            d : { test(); };\
        }\
        service test() {\
            |e|\
            e := 1;\
            return e;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    TEST_PORT_COMPONENT(inst->getPortByName("a")->getPort(), "a", 0);
    TEST_PORT_COMPONENT(inst->getPortByName("b")->getPort(), "b", 0);
    TEST_PORT_COMPONENT(inst->getPortByName("c")->getPort(), "c", 0);
    TEST_PORT_COMPONENT(inst->getPortByName("d")->getPort(), "d", 0);
    ptr(mem_port) port = inst->getPortByName("d")->invokeByName("test");
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 1);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(serviceParamsTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Inst {\
        service test(a, b) {\
            return a + b;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i.test(1, 2);\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 3);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(connection1Test) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
        }\
        architecture {\
            connect a to default@(A.new());\
        }\
        service test() {\
            |b|\
            b := 1;\
            return b + a.add(2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    
    BOOST_CHECK_EQUAL(inst->getPortByName("a")->getConnectedPortsNumber(), 1);
    TEST_PORT_COMPONENT(inst->getPortByName("a")->getConnectedPortAt(0)->getPort(), "default", 0);
    
    ptr(mem_port) port = inst->getServiceByName("test")->invoke();
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(connection2Test) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
        }\
        service test() {\
            |b|\
            b := 1;\
            return b + a.add(2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            connect a@i to default@(A.new());\
            return i.test();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(disconnectionTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        externally requires {\
            a : A;\
        }\
        service test() {\
            |b|\
            b := 1;\
            return b + a.add(2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i j|\
            i := Inst.new();\
            j := A.new();\
            connect a@i to default@j;\
            disconnect a@i from default@j;\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    
    BOOST_CHECK_EQUAL(inst->getPortByName("a")->getConnectedPortsNumber(), 0);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(delegationTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
        }\
        architecture {\
            connect a to default@(A.new());\
            delegate default@self to default@a;\
        }\
        service test() {\
            |b|\
            b := 1;\
            return b + default.add(2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    
    BOOST_CHECK_EQUAL(inst->getPortByName("a")->getConnectedPortsNumber(), 1);
    
    ptr(mem_port) port = inst->getServiceByName("test")->invoke();
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(selfExternalRequirementSourceThrowTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        externally requires {\
            a : A;\
        }\
        architecture {\
            connect a to default@(A.new());\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(selfExternalRequirementDestinationThrowTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        externally requires {\
            a : A;\
        }\
        architecture {\
            connect default@(A.new()) to a;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(outerExternalRequirementSourceThrowTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally provides {\
            b : { add(a); };\
        }\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
            c : { add(a); };\
        }\
        architecture {\
            connect a to default@(A.new());\
            connect c to b@a;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(outerExternalRequirementDestinationThrowTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally provides {\
            b : { add(a); };\
        }\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
            c : { add(a); };\
        }\
        architecture {\
            connect a to default@(A.new());\
            connect b@a to c;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(manualConnectionTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally provides {\
            b : { add(a); };\
        }\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
            c : { add(a); };\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i j|\
            i := Inst.new();\
            j := A.new();\
            connect b@j to c@i;\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(manualDisconnectionTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally provides {\
            b : { add(a); };\
        }\
        service add(a) {\
            return a + 1;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : A;\
            c : { add(a); };\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |i j|\
            i := Inst.new();\
            j := A.new();\
            disconnect b@j from c@i;\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CWrongPortVisibilityException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
