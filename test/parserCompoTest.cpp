#include <iostream>
#include <vector>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "nodes/compo/descriptor.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/requirement.h"
#include "nodes/compo/service.h"
#include "nodes/compo/constraint.h"
#include "nodes/procedural/assignmentExpression.h"
#include "nodes/procedural/constant.h"
#include "nodes/procedural/stringLiteral.h"
#include "nodes/procedural/parens.h"
#include "nodes/procedural/additionExpression.h"
#include "nodes/procedural/subtractionExpression.h"
#include "nodes/procedural/multiplicationExpression.h"
#include "nodes/procedural/divisionExpression.h"
#include "nodes/procedural/equalityExpression.h"
#include "nodes/procedural/nonEqualityExpression.h"
#include "nodes/procedural/logicalOrExpression.h"
#include "nodes/procedural/logicalAndExpression.h"
#include "nodes/procedural/greaterExpression.h"
#include "nodes/procedural/greaterOrEqualExpression.h"
#include "nodes/procedural/lessExpression.h"
#include "nodes/procedural/lessOrEqualExpression.h"

#include "testDefinitions.h"

BOOST_AUTO_TEST_SUITE(parserCompo)

// Global lexer and parser for testing purposes
Lexer lexer;
ParserWrapper parser(&lexer);

BOOST_AUTO_TEST_CASE(compoBasicStructure) {
    // Testing input
    std::stringstream input;
    input.str("descriptor HTTPServer extends server {\
	externally provides {\
		default : {};\
	}\
        externally requires {\
            default : {};\
        }\
	service create() {}\
        constraint httpOnly() {}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "HTTPServer", "server", 4);
    
    // Port names vector
    std::vector<std::string> portNames;
    portNames.push_back("default");
    
    // Check provision
    std::shared_ptr<nodes::compo::CProvision> provision = std::dynamic_pointer_cast<nodes::compo::CProvision>(descriptor->getBodyNodeAt(0)); 
    TEST_PROVISION(provision, nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    std::shared_ptr<nodes::compo::CRequirement> requirement = std::dynamic_pointer_cast<nodes::compo::CRequirement>(descriptor->getBodyNodeAt(1));
    TEST_REQUIREMENT(requirement, nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(2));
    TEST_SERVICE(service, "create", 0, 0, 0);
    
    // Check constraint
    std::shared_ptr<nodes::compo::CConstraint> constraint = std::dynamic_pointer_cast<nodes::compo::CConstraint>(descriptor->getBodyNodeAt(3));
    TEST_CONSTRAINT(constraint, "httpOnly", 0, 0);
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceParams) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
	service noparams() {}\
        service oneparam(param1) {}\
        service twoparams(param1, param2) {}\
        service threeparams(param1, param2, param3) {}\
    }");

    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 4);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "noparams", 0, 0, 0);
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(1));
    TEST_SERVICE(service, "oneparam", 1, 0, 0);
    BOOST_CHECK_EQUAL("param1", service->getParamAt(0)->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(2));
    TEST_SERVICE(service, "twoparams", 2, 0, 0);
    BOOST_CHECK_EQUAL("param1", service->getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service->getParamAt(0)->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(3));
    TEST_SERVICE(service, "threeparams", 3, 0, 0);
    BOOST_CHECK_EQUAL("param1", service->getParamAt(2)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service->getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL("param3", service->getParamAt(0)->getStringValue());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceBody) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service body1() {a;}\
        service body2() {b := 1;}\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 2);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "body1", 0, 1, 0);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(1));
    TEST_SERVICE(service, "body2", 0, 1, 0);
    
    // Check assignment
    std::shared_ptr<nodes::procedural::CAssignmentExpression> assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(assignment->getRValue());
    TEST_CONSTANT(constant, 1);
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceTemporaries) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service temporaries() {\
            | a b |\
        }\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "temporaries", 0, 0, 2);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getTemporaryAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getTemporaryAt(1));
    TEST_SYMBOL(symbol, "b");    
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()