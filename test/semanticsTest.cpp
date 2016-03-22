#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions.h"
#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "ast/visitor/semanticCheckVisitor.h"
#include "ast/semantic/globalDescriptorsTable.h"

BOOST_AUTO_TEST_SUITE(semanticsTest)


// Global lexer and parser for testing purposes
ParserWrapper parser(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());

BOOST_AUTO_TEST_CASE(basic) {
    // Testing input
    std::stringstream input;
    input.str(
    "\
     descriptor server {}\
     \
     descriptor HTTPServer extends server {\
	externally provides {\
		default : {};\
	}\
        externally requires {\
            default : {};\
        }\
        internally provides {\
		default : {};\
	}\
        internally requires {\
            default : {};\
        }\
	service create() {}\
        constraint httpOnly() {}\
        architecture {}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    ptr(ast_program) program = parser.getRootNode();
    
    std::shared_ptr<ast::visitors::CSemanticCheckVisitor> visitor = std::make_shared<ast::visitors::CSemanticCheckVisitor>(parser.getDescriptorTable());

    try {
        program->accept(visitor);
    }
    catch (const exceptions::semantic::CWrongAstNodeTypeException& ex) {
        ex.what();
    }
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()
