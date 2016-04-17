#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
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
#include "ast/visitor/constantsVisitor.h"

BOOST_AUTO_TEST_SUITE(constantsTest)


// Global parser for testing purposes
ParserWrapper parser(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());

BOOST_AUTO_TEST_CASE(complexTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test{\
        service testService() {\
            |a|\
            a := 1;\
            a := \"testString\";\
            a := false;\
            for (i := 1; i < 10; i := i + 1) {\
                i := i + 5;\
            }\
            if (a != 6) {\
                while (a < 10) {\
                    a := a + 15;\
                }\
            }\
            f[3].inv();\
            g.inv(1, \"test\");\
            return a - 5;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    ptr(ast::visitors::CConstantsVisitor) visitor = new_ptr(ast::visitors::CConstantsVisitor)();

    cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(0)->accept(visitor);
    BOOST_CHECK_EQUAL(visitor->getConstantsSize(), 14);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(0))->getValue(), 1);
    BOOST_CHECK_EQUAL(cast(ast_string)(visitor->getConstantAt(1))->getValue(), "testString");
    BOOST_CHECK_EQUAL(cast(ast_boolean)(visitor->getConstantAt(2))->getValue(), false);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(3))->getValue(), 1);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(4))->getValue(), 10);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(5))->getValue(), 1);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(6))->getValue(), 5);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(7))->getValue(), 6);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(8))->getValue(), 10);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(9))->getValue(), 15);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(10))->getValue(), 3);
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(11))->getValue(), 1);
    BOOST_CHECK_EQUAL(cast(ast_string)(visitor->getConstantAt(12))->getValue(), "test");
    BOOST_CHECK_EQUAL(cast(ast_constant)(visitor->getConstantAt(13))->getValue(), 5);
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(returnTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test{\
        service testService(a, b) {\
            return a - b;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    ptr(ast::visitors::CConstantsVisitor) visitor = new_ptr(ast::visitors::CConstantsVisitor)();

    cast(ast_descriptor)(program->getNodeAt(0))->getServiceAt(0)->accept(visitor);
    BOOST_CHECK_EQUAL(visitor->getConstantsSize(), 0);
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_SUITE_END()
