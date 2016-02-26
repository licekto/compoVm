#include <iostream>
#include <vector>

#include <boost/test/unit_test.hpp>

#include "lexer.h"
#include "parserWrapper.h"
#include "compoDescriptor.h"
#include "compoProvision.h"
#include "compoRequirement.h"
#include "compoService.h"
#include "compoConstraint.h"
#include "compoAssignment.h"
#include "compoConstant.h"

void testDescriptor(const compo::CCompoDescriptor& descriptor, const std::string& name, const std::string& extends, int bodySize) {
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::DESCRIPTOR, descriptor.getNodeType());
    BOOST_CHECK_EQUAL(name, descriptor.getName());
    BOOST_CHECK_EQUAL(extends, descriptor.getExtends());
    BOOST_CHECK_EQUAL(bodySize, descriptor.getBodySize());
}

void testReqProv(const compo::CCompoAbstractReqProv *reqProv, compo::NodeTypeEnum type, compo::visibilityType visibility, const std::vector<std::string>& portNames) {
    BOOST_CHECK_EQUAL(type, reqProv->getNodeType());
    BOOST_CHECK_EQUAL(visibility, reqProv->getVisibilityType());
    BOOST_CHECK_EQUAL(portNames.size(), reqProv->getNumberOfPorts());
    
    for (unsigned int i = 0; i < portNames.size(); ++i) {
        BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, reqProv->getPortAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(portNames.at(i), reqProv->getPortAt(i)->getName());
    }
}

void testServConstr(const compo::CCompoAbstractServConstr *servConstr, compo::NodeTypeEnum type, const std::string& name, const std::vector<std::string>& paramNames, int bodySize) {
    BOOST_CHECK_EQUAL(type, servConstr->getNodeType());
    BOOST_CHECK_EQUAL(name, servConstr->getName());
    BOOST_CHECK_EQUAL(paramNames.size(), servConstr->getParamsSize());
    BOOST_CHECK_EQUAL(bodySize, servConstr->getBodySize());
    
    for (unsigned int i = 0; i < paramNames.size(); ++i) {
        BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, servConstr->getParamAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(paramNames.at(i), servConstr->getParamAt(i)->getStringValue());
    }
}

void testSymbol(const compo::CCompoSymbol& symbol, const std::string& name) {
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL(name, symbol.getStringValue());
}

void testConstant(const compo::CCompoConstant& constant, int value) {
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTANT, constant.getNodeType());
    BOOST_CHECK_EQUAL(value, constant.getValue());
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
    compo::CCompoDescriptor *descriptor = dynamic_cast<compo::CCompoDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "HTTPServer", "server", 4);
    
    // Port names vector
    std::vector<std::string> portNames;
    portNames.push_back("default");
    
    // Check provision
    compo::CCompoProvision *provision = dynamic_cast<compo::CCompoProvision*>(descriptor->getBodyNodeAt(0));    
    testReqProv(provision, compo::NodeTypeEnum::PROVISION, compo::visibilityType::EXTERNAL, portNames);
    
    // Check requirement
    compo::CCompoRequirement *requirement = dynamic_cast<compo::CCompoRequirement*>(descriptor->getBodyNodeAt(1));
    testReqProv(requirement, compo::NodeTypeEnum::REQUIREMENT, compo::visibilityType::EXTERNAL, portNames);
    
    // Check service
    compo::CCompoService *service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(2));
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "create", std::vector<std::string>(0), 0);
    
    // Check constraint
    compo::CCompoConstraint *constraint = dynamic_cast<compo::CCompoConstraint *>(descriptor->getBodyNodeAt(3));
    testServConstr(constraint, compo::NodeTypeEnum::CONSTRAINT, "httpOnly", std::vector<std::string>(0), 0);
    
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
    compo::CCompoDescriptor *descriptor = dynamic_cast<compo::CCompoDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 4);
    
    // Parameters vector
    std::vector<std::string> params;
    compo::CCompoService *service;
    
    // Check service
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(0));
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "noparams", params, 0);
    
    // Check service
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(1));
    params.push_back("param1");
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "oneparam", params, 0);
    
    // Check service
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(2));
    params.clear();
    params.push_back("param2");
    params.push_back("param1");
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "twoparams", params, 0);
    
    // Check service
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(3));
    params.clear();
    params.push_back("param3");
    params.push_back("param2");
    params.push_back("param1");
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "threeparams", params, 0);
    
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
    compo::CCompoDescriptor *descriptor = dynamic_cast<compo::CCompoDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 2);
    
    // Check service
    compo::CCompoService *service = dynamic_cast<compo::CCompoService*>(descriptor->getBodyNodeAt(0));
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "body1", std::vector<std::string>(0), 1);
    
    // Check symbol
    compo::CCompoSymbol *symbol = dynamic_cast<compo::CCompoSymbol*>(service->getBodyNodeAt(0));
    testSymbol(*symbol, "a");
    
    // Check service
    service = dynamic_cast<compo::CCompoService*>(descriptor->getBodyNodeAt(1));
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "body2", std::vector<std::string>(0), 1);
    
    // Check assignment
    compo::CCompoAssignment *assignment = dynamic_cast<compo::CCompoAssignment*>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::ASSIGNMENT, assignment->getNodeType());
    
    // Check symbol
    symbol = dynamic_cast<compo::CCompoSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "b");
    
    // Check constant
    compo::CCompoConstant *constant = dynamic_cast<compo::CCompoConstant*>(assignment->getRValue());
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
        }\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    // Check descriptor
    compo::CCompoDescriptor *descriptor = dynamic_cast<compo::CCompoDescriptor*>(parser.getRootNodeAt(0));
    testDescriptor(*descriptor, "test", "", 1);
    
    // Check service
    compo::CCompoService *service = dynamic_cast<compo::CCompoService*>(descriptor->getBodyNodeAt(0));
    testServConstr(service, compo::NodeTypeEnum::SERVICE, "procedural", std::vector<std::string>(0), 3);
    
    // Check symbol
    compo::CCompoSymbol *symbol = dynamic_cast<compo::CCompoSymbol*>(service->getBodyNodeAt(0));
    testSymbol(*symbol, "a");
    
    compo::CCompoAssignment *assignment = dynamic_cast<compo::CCompoAssignment*>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::ASSIGNMENT, assignment->getNodeType());
    
    symbol = dynamic_cast<compo::CCompoSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "b");
    
    compo::CCompoConstant *constant = dynamic_cast<compo::CCompoConstant*>(assignment->getRValue());
    testConstant(*constant, 1);
    
    assignment = dynamic_cast<compo::CCompoAssignment*>(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::ASSIGNMENT, assignment->getNodeType());
    
    symbol = dynamic_cast<compo::CCompoSymbol*>(assignment->getVariable());
    testSymbol(*symbol, "c");
    
    parser.clear();
}

BOOST_AUTO_TEST_SUITE_END()