#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions.h"
#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "ast/visitor/semanticCheckVisitor.h"
#include "ast/semantic/globalDescriptorsTable.h"
#include "exceptions/semantic/emptyProgramException.h"

BOOST_AUTO_TEST_SUITE(semanticsTest)


// Global parser for testing purposes
ParserWrapper parser(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());

BOOST_AUTO_TEST_CASE(basicTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "\
     descriptor server {}\
     \
     descriptor HTTPServer extends server {\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser.getDescriptorTable());

    program->accept(visitor);
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(emptyTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "");
    
    // Parse input and create AST
    parser.parse(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser.getDescriptorTable());

    BOOST_CHECK_THROW(program->accept(visitor), exceptions::semantic::CEmptyProgramException);
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(undefinedDescriptorTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor HTTPServer extends server {}");
    
    // Parse input and create AST
    parser.parse(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    ptr(ast::visitors::CSemanticCheckVisitor) visitor = new_ptr(ast::visitors::CSemanticCheckVisitor)(parser.getDescriptorTable());
    
    BOOST_CHECK_THROW(program->accept(visitor), exceptions::semantic::CUndefinedDescriptorException);
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_SUITE_END()
