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
#include "exceptions/semantic/externalPortConnectionException.h"

BOOST_AUTO_TEST_SUITE(interpreterCompoTest)

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
            disconnect a@i from default@a;\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    
    BOOST_CHECK_EQUAL(inst->getPortByName("a")->getConnectedPortsNumber(), 0);
    
    BOOST_CHECK_THROW(inst->getServiceByName("test")->invoke(), exceptions::runtime::CServiceNotFoundException);
    
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

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CExternalPortConnectionException);
    
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

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CExternalPortConnectionException);
    
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
        \
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

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CExternalPortConnectionException);
    
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

    BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CExternalPortConnectionException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(internalProvisionTest) {
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
    }\
    descriptor CompoContainer {\
        service main() {\
            |i|\
            i := Inst.new();\
            connect a@i to default@(A.new());\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    interpreter->run(program);
    //BOOST_CHECK_THROW(interpreter->run(program), exceptions::semantic::CExternalPortConnectionException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(complexTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Add {\
        provides {\
            provAdd : { add(a, b); };\
        }\
        service add(a, b) {\
            return a + b;\
        }\
        service testAdd(a, b) {\
            return a + b + 2;\
        }\
    }\
    descriptor Sub {\
        provides {\
            provSub : { sub(a, b); };\
        }\
        service sub(a, b) {\
            return a - b;\
        }\
        service testSub(a, b) {\
            return a - b - 2;\
        }\
    }\
    descriptor Div {\
        provides {\
            provDiv : { div(a, b); };\
        }\
        service div(a, b) {\
            return a / b;\
        }\
        service testDiv(a, b) {\
            return a / b / 2;\
        }\
    }\
    descriptor Mul {\
        provides {\
            provMul : { mul(a, b); };\
        }\
        service mul(a, b) {\
            return a * b;\
        }\
        service testMul(a, b) {\
            return a * b * 2;\
        }\
    }\
    descriptor Inst {\
        internally requires {\
            a : { add(a, b); };\
            b : Sub;\
        }\
        externally requires {\
            c : { div(a, b); };\
            d : Mul;\
        }\
        internally provides {\
            e : { testInternal(a); };\
        }\
        externally provides {\
            g : { test(); };\
        }\
        architecture {\
            connect a to default@(Add.new());\
            connect b to default@(Sub.new());\
            connect c to default@(Div.new());\
            connect d to default@(Mul.new());\
        }\
        service testInternal(a) {\
            return 1 + a;\
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

//    ptr(mem_component) inst = interpreter->run(program)->getOwner();
//    
//    BOOST_CHECK_EQUAL(inst->getPortByName("a")->getConnectedPortsNumber(), 1);
//    
//    ptr(mem_port) port = inst->getServiceByName("test")->invoke();
//    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(calcTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Calc {\
        provides {\
                arithmetic : { add(x,y); mul(x,y); pow(base,exp) };\
                probability : { rand() };\
        }\
        requires {\
                randGen : { getRandVal(seed) };\
        }\
        service add(x, y) { return x+y; }\
        service mul(x, y) { return x*y; }\
        service pow(base, exp) {\
                | res i |\
                res := 1;\
                for (i := 0; i < exp; i := i + 1) {\
                        res := self.mul(res, base);\
                }\
                return res;\
        }\
        service rand() {\
                return randGen.getRandVal(101);\
        }\
    }\
\
    descriptor RandomGen {\
        provides {\
            default : { getRandVal(seed) };\
        }\
        service getRandVal(seed) {\
            return 15;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            c := Calc.new();\
            connect randGen@c to default@(RandomGen.new());\
            c.add(c.rand(),1);\
            c.mul(3,c.pow(2,3));\
        }\
    }");
    
    // Parse input and create AST
    //parser->parseAll(input);
    
    //ptr(ast_program) program = parser->getRootNode();
    
    
    //ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser->getDescriptorTable());

    //program->accept(visitor);
    
    //interpreter::core::CInterpreter interpreter(parser, new_ptr(interpreter::core::CBootstrap)());
    
    //interpreter.run(program);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
