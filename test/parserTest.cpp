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

void testDescriptor(std::shared_ptr<nodes::compo::CDescriptor> descriptor, const std::string& name, const std::string& extends, int bodySize) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DESCRIPTOR, descriptor->getNodeType());
    BOOST_CHECK_EQUAL(name, descriptor->getName());
    BOOST_CHECK_EQUAL(extends, descriptor->getExtends());
    BOOST_CHECK_EQUAL(bodySize, descriptor->getBodySize());
}

void testReqProv(std::shared_ptr<nodes::compo::CAbstractReqProv> reqProv, nodes::types::nodeType type, nodes::types::visibilityType visibility, const std::vector<std::string>& portNames) {
    BOOST_CHECK_EQUAL(type, reqProv->getNodeType());
    BOOST_CHECK_EQUAL(visibility, reqProv->getVisibilityType());
    BOOST_CHECK_EQUAL(portNames.size(), reqProv->getNumberOfPorts());
    
    for (unsigned int i = 0; i < portNames.size(); ++i) {
        BOOST_CHECK_EQUAL(nodes::types::nodeType::PORT, reqProv->getPortAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(portNames.at(i), reqProv->getPortAt(i)->getName());
    }
}

void testServConstr(std::shared_ptr<nodes::compo::CAbstractServConstr> servConstr, nodes::types::nodeType type, const std::string& name, const std::vector<std::string>& paramNames, int bodySize) {
    BOOST_CHECK_EQUAL(type, servConstr->getNodeType());
    BOOST_CHECK_EQUAL(name, servConstr->getName());
    BOOST_CHECK_EQUAL(paramNames.size(), servConstr->getParamsSize());
    BOOST_CHECK_EQUAL(bodySize, servConstr->getBodySize());
    
    for (unsigned int i = 0; i < paramNames.size(); ++i) {
        BOOST_CHECK_EQUAL(nodes::types::nodeType::SYMBOL, servConstr->getParamAt(i)->getNodeType());
        BOOST_CHECK_EQUAL(paramNames.at(i), servConstr->getParamAt(i)->getStringValue());
    }
}

void testSymbol(std::shared_ptr<nodes::procedural::CSymbol> symbol, const std::string& name) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SYMBOL, symbol->getNodeType());
    BOOST_CHECK_EQUAL(name, symbol->getStringValue());
}

void testConstant(std::shared_ptr<nodes::procedural::CConstant> constant, int value) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, constant->getNodeType());
    BOOST_CHECK_EQUAL(value, constant->getValue());
}

void testStringLiteral(std::shared_ptr<nodes::procedural::CStringLiteral> stringLiteral, std::string value) {
    BOOST_CHECK_EQUAL(nodes::types::nodeType::STRING_LITERAL, stringLiteral->getNodeType());
    BOOST_CHECK_EQUAL(value, stringLiteral->getValue());
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
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    testDescriptor(descriptor, "HTTPServer", "server", 4);
    
    // Port names vector
    std::vector<std::string> portNames;
    portNames.push_back("default");
    
    // Check provision
    std::shared_ptr<nodes::compo::CProvision> provision = std::dynamic_pointer_cast<nodes::compo::CProvision>(descriptor->getBodyNodeAt(0));    
    testReqProv(provision, nodes::types::nodeType::PROVISION, nodes::types::visibilityType::EXTERNAL, portNames);
    
    // Check requirement
    std::shared_ptr<nodes::compo::CRequirement> requirement = std::dynamic_pointer_cast<nodes::compo::CRequirement>(descriptor->getBodyNodeAt(1));
    testReqProv(requirement, nodes::types::nodeType::REQUIREMENT, nodes::types::visibilityType::EXTERNAL, portNames);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(2));
    testServConstr(service, nodes::types::nodeType::SERVICE, "create", std::vector<std::string>(0), 0);
    
    // Check constraint
    std::shared_ptr<nodes::compo::CConstraint> constraint = std::dynamic_pointer_cast<nodes::compo::CConstraint>(descriptor->getBodyNodeAt(3));
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
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    testDescriptor(descriptor, "test", "", 4);
    
    // Parameters vector
    std::vector<std::string> params;
    std::shared_ptr<nodes::compo::CService> service;
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "noparams", params, 0);
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(1));
    params.push_back("param1");
    testServConstr(service, nodes::types::nodeType::SERVICE, "oneparam", params, 0);
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(2));
    params.clear();
    params.push_back("param2");
    params.push_back("param1");
    testServConstr(service, nodes::types::nodeType::SERVICE, "twoparams", params, 0);
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(3));
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
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    testDescriptor(descriptor, "test", "", 2);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "body1", std::vector<std::string>(0), 1);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getBodyNodeAt(0));
    testSymbol(symbol, "a");
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(1));
    testServConstr(service, nodes::types::nodeType::SERVICE, "body2", std::vector<std::string>(0), 1);
    
    // Check assignment
    std::shared_ptr<nodes::procedural::CAssignmentExpression> assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "b");
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(assignment->getRValue());
    testConstant(constant, 1);
    
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
            e := 15 + 64;\
            f := 18 - 2;\
            g := 5 * 3;\
            h := 10 / 5;\
        }\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    testDescriptor(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    testServConstr(service, nodes::types::nodeType::SERVICE, "procedural", std::vector<std::string>(0), 8);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getBodyNodeAt(0));
    testSymbol(symbol, "a");
    
    
    // Check assignment
    std::shared_ptr<nodes::procedural::CAssignmentExpression> assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "b");
    
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(assignment->getRValue());
    testConstant(constant, 1);
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "c");
    
    // Check string literal
    std::shared_ptr<nodes::procedural::CStringLiteral> stringLiteral = std::dynamic_pointer_cast<nodes::procedural::CStringLiteral>(assignment->getRValue());
    testStringLiteral(stringLiteral, "testString");
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "d");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CParens> parens = std::dynamic_pointer_cast<nodes::procedural::CParens>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::PARENS, parens->getNodeType());
    
    // Check constant
    constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(parens->getExpression());
    testConstant(constant, 55);
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(4));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "e");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CAdditionExpression> addition = std::dynamic_pointer_cast<nodes::procedural::CAdditionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ADDITION_EXPRESSION, addition->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::PLUS, addition->getOperator());
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(addition->getOperand1());
    testConstant(op1, 15);
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(addition->getOperand2());
    testConstant(op2, 64);
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(5));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "f");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CSubtractionExpression> subtraction = std::dynamic_pointer_cast<nodes::procedural::CSubtractionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SUBTRACTION_EXPRESSION, subtraction->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::MINUS, subtraction->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(subtraction->getOperand1());
    testConstant(op1, 18);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(subtraction->getOperand2());
    testConstant(op2, 2);
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(6));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "g");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CMultiplicationExpression> multiplication = std::dynamic_pointer_cast<nodes::procedural::CMultiplicationExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::MULTIPLICATION_EXPRESSION, multiplication->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::TIMES, multiplication->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(multiplication->getOperand1());
    testConstant(op1, 5);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(multiplication->getOperand2());
    testConstant(op2, 3);
    
    
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(7));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    testSymbol(symbol, "h");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CDivisionExpression> division = std::dynamic_pointer_cast<nodes::procedural::CDivisionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DIVISION_EXPRESSION, division->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::DIVISION, division->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(division->getOperand1());
    testConstant(op1, 10);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(division->getOperand2());
    testConstant(op2, 5);
    
    parser.clear();
}

BOOST_AUTO_TEST_SUITE_END()