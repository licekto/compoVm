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

BOOST_AUTO_TEST_SUITE(interpreterReflectionTest)

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

BOOST_AUTO_TEST_CASE(basicDescriptorTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally requires {\
            name : String;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a|\
            a := A.new();\
            return a.getDescriptor();\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    TEST_DESCRIPTOR_COMPONENT(component, "A", "", 1, 1, 0);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(portNameTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally requires {\
            name : String;\
        }\
        externally requires {\
            abcd : String;\
        }\
        internally provides {\
            xyz : String;\
        }\
        service setName(newName) {\
            name := newName;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a n res|\
            a := A.new();\
            n := a.getPortNamed(\"name\");\
            res := n.getName();\
            n := a.getPortNamed(\"abcd\");\
            res := res + \" \" + n.getName();\
            n := a.getPortNamed(\"xyz\");\
            res := res + \" \" + n.getName();\
            return res;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_string)(component)->getValue(), "name abcd xyz");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(descriptorNameTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor Z {\
    }\
    descriptor A extends Z {\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a desc res b|\
            a := A.new();\
            desc := a.getDescriptor();\
            desc.setName(\"B\");\
            res := desc.getName();\
            b := B.new();\
            desc := b.getDescriptor();\
            desc.setName(\"C\");\
            res := res + \" \" + desc.getName() + \" \" + desc.getParentName();\
            desc.setParentName(\"Y\");\
            res := res + \" \" + desc.getParentName();\
            return res;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_string)(component)->getValue(), "B C Z Y");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(serviceAdditionTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a b desc srv|\
            a := A.new();\
            desc := a.getDescriptor();\
            srv := Service.new();\
            srv.setName(\"test\");\
            srv.addParam(\"param1\");\
            srv.addParam(\"param2\");\
            srv.setCode(\"{ return param1 + param2; }\");\
            desc.addService(srv);\
            b := A.new();\
            return b.test(1, 2);\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_int)(component)->getValue(), 3);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(gettersTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        internally requires {\
            testName : String;\
        }\
        architecture {\
            connect testName to default;\
        }\
        service testService(p) {\
            return 1 + 1;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a res|\
            a := A.getDescribedPortAt(0);\
            res := \"PORT: \" + a.getName() + \" \" + a.getVisibility() + \" \" + a.getRole() + \", is collection: \" + a.isCollection();\
            a := A.getDescribedConnAt(0);\
            res := res + \", CONN: \" + a.getSourceType() + \" \" + a.getSourceComponent() + \" \" + a.getSourcePort();\
            a := A.getService(\"testService\", 1);\
            res := res + \", SERV: \" + a.getName();\
            return res;\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    ptr(mem_component) component = interpreter->run(program)->getOwner();
    BOOST_CHECK_EQUAL(cast(mem_string)(component)->getValue(), "PORT: testName internally requires, is collection: false, CONN: named self testName, SERV: testService");
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_CASE(removeServiceTest) {
    // Testing input
    std::stringstream input;
    input.str(
   "descriptor A {\
        service testService(p) {\
            return 1 + p;\
        }\
    }\
    descriptor CompoContainer {\
        service main() {\
            |a|\
            A.removeService(\"testService\", 1);\
            a := A.new();\
            a.testService(1);\
        }\
    }");
    
    // Parse input and create AST
    parser->parseAll(input);
    
    ptr(ast_program) program = parser->getRootNode();
    BOOST_CHECK_THROW(interpreter->run(program), exceptions::runtime::CServiceNotFoundException);
    
    // Clear AST for next test
    parser->clearAll();
    table->clear();
}

BOOST_AUTO_TEST_SUITE_END()
