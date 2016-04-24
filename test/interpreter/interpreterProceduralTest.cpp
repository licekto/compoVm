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
#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap/bootstrapStage1.h"

BOOST_AUTO_TEST_SUITE(interpreterProceduralTest)

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

BOOST_AUTO_TEST_CASE(binaryOperatorsTest) {
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

BOOST_AUTO_TEST_CASE(forLoopTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |i cnt|\
            cnt := 0;\
            for (i := 1; i < 4; i := i + 1) {\
                cnt := cnt + i;\
            }\
            return cnt;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 6);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(whileLoopTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |cnt|\
            cnt := 0;\
            while(cnt < 4) {\
                cnt := cnt + 1;\
            }\
            return cnt;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(continueForTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |i cnt|\
            cnt := 0;\
            for (i := 1; i < 4; i := i + 1) {\
                continue;\
                cnt := cnt + i;\
            }\
            return cnt;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 0);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(breakForTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |i cnt|\
            cnt := 0;\
            for (i := 1; i < 4; i := i + 1) {\
                cnt := cnt + i;\
                break;\
            }\
            return cnt;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 1);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(breakWhileTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |cnt|\
            cnt := 0;\
            while(cnt < 4) {\
                cnt := cnt + 1;\
                break;\
            }\
            return cnt;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 1);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(continueWhileTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |cnt a|\
            cnt := 0;\
            a := 0;\
            while(cnt < 4) {\
                cnt := cnt + 1;\
                continue;\
                a := a + 1;;\
            }\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 0);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(ifTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |cnt a|\
            cnt := 10;\
            a := 0;\
            if (cnt > 9) {\
                a := a + 5;\
            }\
            if (a <= 5) {\
                a := 13 - a;\
            }\
            if (a != 8) {\
                a := a + 5;\
            }\
            else {\
                a := a * 3;\
            }\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 24);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(elseIfTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |a|\
            a := 2;\
            if (a == 8) {\
                a := a + 5;\
            }\
            else if (a != 1) {\
                a := a * 3;\
            }\
            else {\
                a := 5;\
            }\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_port) port = interpreter->run(program);
    BOOST_CHECK_EQUAL(cast(mem_int)(port->getOwner())->getValue(), 6);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
