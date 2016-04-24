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
#include "exceptions/semantic/wrongPortVisibiltyException.h"
#include "ast/visitor/printVisitor.h"
#include "exceptions/runtime/wrongStringOperationException.h"

BOOST_AUTO_TEST_SUITE(interpreterValuesTest)

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

BOOST_AUTO_TEST_CASE(valuesTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Person {\
        internally requires {\
            name : String;\
            age : Int;\
            married : Bool;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
        service getName() {\
            return name;\
        }\
        service setAge(newAge) {\
            age := newAge;\
        }\
        service getAge() {\
            return age;\
        }\
        service setMarried(isMarried) {\
            married := isMarried;\
        }\
        service getMarried() {\
            return married;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |p|\
            p := Person.new();\
            p.setName(\"Linus\");\
            p.setAge(46);\
            p.setMarried(true);\
            return p;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    
    BOOST_CHECK_EQUAL(component->getPortByName("name")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_string)(component->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "Linus");
    BOOST_CHECK_EQUAL(component->getPortByName("age")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_int)(component->getPortByName("age")->getConnectedPortAt(0)->getOwner())->getValue(), 46);
    BOOST_CHECK_EQUAL(component->getPortByName("married")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_bool)(component->getPortByName("married")->getConnectedPortAt(0)->getOwner())->getValue(), true);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(stringConcatenationTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |str|\
            str := \"abc\" + \"xyz\" + false + 5486;\
            return str;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_string)(component)->getValue(), "abcxyzfalse5486");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(stringConcatenationFailTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |str|\
            str := \"qwe\" + \"abc\" - \"xyz\" * false / 5486;\
            return str;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    BOOST_CHECK_THROW(interpreter->run(program)->getOwner(), exceptions::runtime::CWrongStringOperationException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(serviceInvocationBinaryOpTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service add(a, b) {\
            return a + b;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a i|\
            a := A.new();\
            i := 1 + a.add(1,2);\
            return i;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) comp = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(comp)->getValue(), 4);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(stringCompareTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor CompoContainer {\
        service main() {\
            |s1 s2 b res|\
            s1 := \"hello\";\
            s2 := \"world\";\
            b := s1 == s2;\
            res := b;\
            s1 := \"world\";\
            b := s1 != s2;\
            res := res + \" \" + b;\
            b := s1 == s2;\
            res := res + \" \" + b;\
            return res;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) comp = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_string)(comp)->getValue(), "false false true");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
