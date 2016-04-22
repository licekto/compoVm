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

BOOST_AUTO_TEST_SUITE(interpreterInheritanceTest)

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

BOOST_AUTO_TEST_CASE(basicTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally requires {\
            a : Int;\
        }\
        service setA(newA) {\
            a := newA;\
        }\
        service getA() {\
            return a;\
        }\
    }\
    descriptor B extends A {\
        service setB(newA) {\
            super.setA(newA * 2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |b|\
            b := B.new();\
            b.setB(4);\
            return b.getA();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 8);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(serviceSpecializationTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally requires {\
            a : Int;\
        }\
        service setA(newA) {\
            a := newA;\
        }\
        service getA() {\
            return a;\
        }\
    }\
    descriptor B extends A {\
        service setA(newA) {\
            super.setA(newA * 2);\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |b|\
            b := B.new();\
            b.setA(4);\
            return b.getA();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

    ptr(mem_component) inst = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(inst)->getValue(), 8);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(complexTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Person {\
        internally requires {\
            name : String;\
            sallary : Int;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
        service getName() {\
            return name;\
        }\
        service setSallary(newSallary) {\
            sallary := newSallary;\
        }\
        service getSallary() {\
            return sallary;\
        }\
    }\
    descriptor Worker extends Person {\
        internally requires {\
            hours : Int;\
        }\
        service setSallary(newSallary) {\
            super.setSallary(newSallary * 2);\
        }\
        service setHours(newHours) {\
            hours := newHours;\
        }\
        service getHours() {\
            return hours;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |person worker sallaries names result|\
            person := Person.new();\
            worker := Worker.new();\
            person.setName(\"Bill\");\
            worker.setName(\"Linus\");\
            person.setSallary(20);\
            worker.setSallary(20);\
            worker.setHours(5);\
            sallaries := worker.getSallary() + person.getSallary();\
            names := person.getName() + \" \" + worker.getName();\
            result := sallaries + \": \" + names + \", hours of \" + worker.getName() + \" - \" + worker.getHours();\
            return result;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();

//    ptr(mem_component) inst = interpreter->run(program)->getOwner();
//    BOOST_CHECK_EQUAL(cast(mem_string)(inst)->getValue(), "60: Bill Linus, hours of Linux - 5");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
