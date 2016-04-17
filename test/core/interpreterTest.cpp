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

BOOST_AUTO_TEST_SUITE(interpreterTest)

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
            |a|\
            a := 1;\
            return a;\
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

BOOST_AUTO_TEST_CASE(binaryOperatorsTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service plusOp() {\
            |a|\
            a := 150 + 30;\
            return a;\
        }\
        service minusOp() {\
            |a|\
            a := 150 - 30;\
            return a;\
        }\
        service timesOp() {\
            |a|\
            a := 150 * 30;\
            return a;\
        }\
        service divideOp() {\
            |a|\
            a := 150 / 30;\
            return a;\
        }\
        service orTrueOp() {\
            |a|\
            a := true || false;\
            return a;\
        }\
        service orFalseOp() {\
            |a|\
            a := false || false;\
            return a;\
        }\
        service andTrueOp() {\
            |a|\
            a := true && true;\
            return a;\
        }\
        service andFalseOp() {\
            |a|\
            a := true && false;\
            return a;\
        }\
        service lessTrueOp() {\
            |a|\
            a := 15 < 20;\
            return a;\
        }\
        service lessFalseOp() {\
            |a|\
            a := 35 < 20;\
            return a;\
        }\
        service lessEqTrueOp() {\
            |a|\
            a := 15 <= 15;\
            return a;\
        }\
        service lessEqFalseOp() {\
            |a|\
            a := 15 <= 14;\
            return a;\
        }\
        service greaterTrueOp() {\
            |a|\
            a := 30 > 20;\
            return a;\
        }\
        service greaterFalseOp() {\
            |a|\
            a := 10 > 20;\
            return a;\
        }\
        service greaterEqTrueOp() {\
            |a|\
            a := 15 >= 15;\
            return a;\
        }\
        service greaterEqFalseOp() {\
            |a|\
            a := 11 >= 14;\
            return a;\
        }\
        service eqTrueOp() {\
            |a|\
            a := 30 == 30;\
            return a;\
        }\
        service eqFalseOp() {\
            |a|\
            a := 10 == 20;\
            return a;\
        }\
        service nonEqTrueOp() {\
            |a|\
            a := 15 != 10;\
            return a;\
        }\
        service nonEqFalseOp() {\
            |a|\
            a := 11 != 11;\
            return a;\
        }\
        service main() {\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_port) port;
    
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(0)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 180);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(1)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 120);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(2)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 4500);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(3)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 5);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(4)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(5)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(6)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(7)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(8)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(9)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(10)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(11)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(12)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(13)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(14)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(15)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(16)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(17)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(18)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(19)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(binaryOperatorsComplexTest) {
    ptr(core_interpreter) interpreter = initInterpreter();
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service complexTest0() {\
            |a|\
            a := 15 / 3;\
            a := a * 20;\
            a := 105 - a;\
            a := a + 25;\
            return a;\
        }\
        service complexTest1() {\
            |a|\
            a := (15 / 3) * 5 - 15 + 25;\
            return a;\
        }\
        service complexTest2() {\
            |a|\
            a := (250 / 50) * (5 - 15) + 25;\
            return a;\
        }\
        service complexTest3() {\
            |a|\
            a := 10 - 20;\
            return a;\
        }\
        service complexTest4() {\
            |a b c|\
            a := 10;\
            b := -13;\
            c := 44;\
            return a + (c * b) / 2;\
        }\
        service complexTest5() {\
            |a b c|\
            a := true;\
            b := false;\
            c := true;\
            return (a || b) && c;\
        }\
        service complexTest6() {\
            |a b c|\
            a := false;\
            b := false;\
            c := true;\
            return (a || b) && c;\
        }\
        service complexTest7() {\
            |a b c|\
            a := 10;\
            b := 15;\
            c := 151;\
            return (a > b) || (c >= a);\
        }\
        service main() {\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port;
    
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(0)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 30);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(1)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 35);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(2)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), -25);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(3)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), -10);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(4)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), -276);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(5)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(6)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), false);
    port = interpreter->execServiceCode(cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(7)->getBodyCode());
    BOOST_CHECK_EQUAL(cast(mem_bool)(port->getOwner())->getValue(), true);
    
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
