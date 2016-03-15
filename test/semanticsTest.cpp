#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "testDefinitions.h"
#include "definitions.h"

BOOST_AUTO_TEST_SUITE(semanticsTest)


// Global lexer and parser for testing purposes
Lexer lexer;
ParserWrapper parser(&lexer);

BOOST_AUTO_TEST_CASE(basic) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor HTTPServer extends server {\
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
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "HTTPServer", "server", 1, 1);
    
    // Check provision
    ptr(ast_provision) provision = cast(ast_provision)(descriptor->getExProvision());
    TEST_PROVISION(provision, ast::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    ptr(ast_requirement) requirement = cast(ast_requirement)(descriptor->getExRequirement());
    TEST_REQUIREMENT(requirement, ast::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check provision
    provision = cast(ast_provision)(descriptor->getInProvision());
    TEST_PROVISION(provision, ast::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    requirement = cast(ast_requirement)(descriptor->getInRequirement());
    TEST_REQUIREMENT(requirement, ast::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "create", 0, 0, 0);
    
    // Check constraint
    ptr(ast_constraint) constraint = cast(ast_constraint)(descriptor->getConstraintAt(0));
    TEST_CONSTRAINT(constraint, "httpOnly", 0, 0);
    
    // Check architecture
    ptr(ast_architecture) architecture = cast(ast_architecture)(descriptor->getArchitecture());
    BOOST_CHECK_EQUAL(ast::types::nodeType::ARCHITECTURE, architecture->getNodeType());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()
