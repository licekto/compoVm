#include <iostream>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "nodes/compo/descriptor.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/requirement.h"
#include "nodes/compo/service.h"
#include "nodes/compo/constraint.h"
#include "nodes/procedural/assignment.h"
#include "nodes/procedural/constant.h"
#include "nodes/procedural/stringLiteral.h"
#include "nodes/procedural/parens.h"

void testDescriptor(const nodes::compo::CDescriptor& descriptor, const std::string& name, const std::string& extends, int bodySize) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DESCRIPTOR, descriptor.getNodeType());
    BOOST_CHECK_EQUAL(name, descriptor.getName());
    BOOST_CHECK_EQUAL(extends, descriptor.getExtends());
    BOOST_CHECK_EQUAL(bodySize, descriptor.getBodySize());
}

void testReqProv(const nodes::compo::CAbstractReqProv *reqProv, nodes::types::nodeType type, nodes::types::visibilityType visibility, const std::vector<std::string>& portNames) {
    BOOST_CHECK_EQUAL(type, reqProv->getNodeType());
    BOOST_CHECK_EQUAL(visibility, reqProv->getVisibilityType());
    BOOST_CHECK_EQUAL(portNames.size(), reqProv->getNumberOfPorts());
    
    for (unsigned int i = 0; i < portNames.size(); ++i) {
        BOOST_CHECK_EQUAL(nodes::types::nodeType::PORT, reqProv->getPortAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(portNames.at(i), reqProv->getPortAt(i)->getName());
    }
}

void testServConstr(const nodes::compo::CAbstractServConstr *servConstr, nodes::types::nodeType type, const std::string& name, const std::vector<std::string>& paramNames, int bodySize) {
    BOOST_CHECK_EQUAL(type, servConstr->getNodeType());
    BOOST_CHECK_EQUAL(name, servConstr->getName());
    BOOST_CHECK_EQUAL(paramNames.size(), servConstr->getParamsSize());
    BOOST_CHECK_EQUAL(bodySize, servConstr->getBodySize());
    
    for (unsigned int i = 0; i < paramNames.size(); ++i) {
        BOOST_CHECK_EQUAL(nodes::types::nodeType::SYMBOL, servConstr->getParamAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(paramNames.at(i), servConstr->getParamAt(i)->getStringValue());
    }
}

void testSymbol(const nodes::procedural::CSymbol& symbol, const std::string& name) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL(name, symbol.getStringValue());
}

void testConstant(const nodes::procedural::CConstant& constant, int value) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, constant.getNodeType());
    BOOST_CHECK_EQUAL(value, constant.getValue());
}

void testStringLiteral(const nodes::procedural::CStringLiteral& stringLiteral, std::string value) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::STRING_LITERAL, stringLiteral.getNodeType());
    BOOST_CHECK_EQUAL(value, stringLiteral.getValue());
}

BOOST_AUTO_TEST_SUITE(parser)

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
    nodes::compo::CDescriptor *descriptor = dynamic_cast<nodes::compo::CDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "HTTPServer", "server", 4);
    
    // Port names vector
    std::vector<std::string> portNames;
    portNames.push_back("default");
    
    // Check provision
    nodes::compo::CProvision *provision = dynamic_cast<nodes::compo::CProvision*>(descriptor->getBodyNodeAt(0));    
    testReqProv(provision, nodes::types::nodeType::PROVISION, nodes::types::visibilityType::EXTERNAL, portNames);
    
    // Check requirement
    nodes::compo::CRequirement *requirement = dynamic_cast<nodes::compo::CRequirement*>(descriptor->getBodyNodeAt(1));
    testReqProv(requirement, nodes::types::nodeType::REQUIREMENT, nodes::types::visibilityType::EXTERNAL, portNames);
    
    // Check service
    nodes::compo::CService *service = dynamic_cast<nodes::compo::CService *>(descriptor->getBodyNodeAt(2));
    testServConstr(service, nodes::types::nodeType::SERVICE, "create", std::vector<std::string>(0), 0);
    
    // Check constraint
    nodes::compo::CConstraint *constraint = dynamic_cast<nodes::compo::CConstraint *>(descriptor->getBodyNodeAt(3));
    testServConstr(constraint, nodes::types::nodeType::CONSTRAINT, "httpOnly", std::vector<std::string>(0), 0);
    
    // Clear AST for next test
    parser.clear();
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
    nodes::compo::CDescriptor *descriptor = dynamic_cast<nodes::compo::CDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 4);
    
    // Parameters vector
    std::vector<std::string> params;
    nodes::compo::CService *service;
    
    // Check service
    service = dynamic_cast<nodes::compo::CService *>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "noparams", params, 0);
    
    // Check service
    service = dynamic_cast<nodes::compo::CService *>(descriptor->getBodyNodeAt(1));
    params.push_back("param1");
    testServConstr(service, nodes::types::nodeType::SERVICE, "oneparam", params, 0);
    
    // Check service
    service = dynamic_cast<nodes::compo::CService *>(descriptor->getBodyNodeAt(2));
    params.clear();
    params.push_back("param2");
    params.push_back("param1");
    testServConstr(service, nodes::types::nodeType::SERVICE, "twoparams", params, 0);
    
    // Check service
    service = dynamic_cast<nodes::compo::CService *>(descriptor->getBodyNodeAt(3));
    params.clear();
    params.push_back("param3");
    params.push_back("param2");
    params.push_back("param1");
    testServConstr(service, nodes::types::nodeType::SERVICE, "threeparams", params, 0);
    
    // Clear AST for next test
    parser.clear();
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
    nodes::compo::CDescriptor *descriptor = dynamic_cast<nodes::compo::CDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 2);
    
    // Check service
    nodes::compo::CService *service = dynamic_cast<nodes::compo::CService*>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "body1", std::vector<std::string>(0), 1);
    
    // Check symbol
    nodes::procedural::CSymbol *symbol = dynamic_cast<nodes::procedural::CSymbol*>(service->getBodyNodeAt(0));
    testSymbol(*symbol, "a");
    
    // Check service
    service = dynamic_cast<nodes::compo::CService*>(descriptor->getBodyNodeAt(1));
    testServConstr(service, nodes::types::nodeType::SERVICE, "body2", std::vector<std::string>(0), 1);
    
    // Check assignment
    nodes::procedural::CAssignment *assignment = dynamic_cast<nodes::procedural::CAssignment*>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT, assignment->getNodeType());
    
    // Check symbol
    symbol = dynamic_cast<nodes::procedural::CSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "b");
    
    // Check constant
    nodes::procedural::CConstant *constant = dynamic_cast<nodes::procedural::CConstant*>(assignment->getRValue());
    testConstant(*constant, 1);
    
    // Clear AST for next test
    parser.clear();
}

BOOST_AUTO_TEST_CASE(compoProcedural) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service procedural() {\
            a;\
            b := 1;\
            c := 'testString';\
            d := (55);\
        }\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    // Check descriptor
    nodes::compo::CDescriptor *descriptor = dynamic_cast<nodes::compo::CDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 1);
    
    // Check service
    nodes::compo::CService *service = dynamic_cast<nodes::compo::CService*>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "procedural", std::vector<std::string>(0), 4);
    
    // Check symbol
    nodes::procedural::CSymbol *symbol = dynamic_cast<nodes::procedural::CSymbol*>(service->getBodyNodeAt(0));
    testSymbol(*symbol, "a");
    
    // Check assignment
    nodes::procedural::CAssignment *assignment = dynamic_cast<nodes::procedural::CAssignment*>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT, assignment->getNodeType());
    
    // Check symbol
    symbol = dynamic_cast<nodes::procedural::CSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "b");
    
    // Check constant
    nodes::procedural::CConstant *constant = dynamic_cast<nodes::procedural::CConstant*>(assignment->getRValue());
    testConstant(*constant, 1);
    
    // Check assignment
    assignment = dynamic_cast<nodes::procedural::CAssignment*>(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT, assignment->getNodeType());
    
    // Check symbol
    symbol = dynamic_cast<nodes::procedural::CSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "c");
    
    // Check string literal
    nodes::procedural::CStringLiteral *stringLiteral = dynamic_cast<nodes::procedural::CStringLiteral*>(assignment->getRValue());
    testStringLiteral(*stringLiteral, "testString");
    
    // Check assignment
    assignment = dynamic_cast<nodes::procedural::CAssignment*>(service->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT, assignment->getNodeType());
    
    // Check symbol
    symbol = dynamic_cast<nodes::procedural::CSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "d");
    
    // Check parens
    nodes::procedural::CParens *parens = dynamic_cast<nodes::procedural::CParens*>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::PARENS, parens->getNodeType());
    
    // Check constant
    constant = dynamic_cast<nodes::procedural::CConstant*>(parens->getExpression());
    testConstant(*constant, 55);
    
    parser.clear();
}

BOOST_AUTO_TEST_SUITE_END()