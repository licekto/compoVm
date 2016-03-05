#include <memory>

#include <boost/test/unit_test.hpp>

#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "nodes/compo/descriptor.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/requirement.h"
#include "nodes/compo/service.h"
#include "nodes/compo/constraint.h"
#include "nodes/compo/architecture.h"
#include "nodes/compo/namedPort.h"
#include "nodes/compo/universalPort.h"
#include "nodes/compo/connection.h"
#include "nodes/compo/disconnection.h"
#include "nodes/compo/dereferenceLiteral.h"
#include "nodes/compo/serviceInvocation.h"
#include "nodes/compo/collectionPortLiteral.h"
#include "nodes/procedural/stringLiteral.h"
#include "nodes/procedural/parens.h"

BOOST_AUTO_TEST_SUITE(parserCompoTest)

// Global lexer and parser for testing purposes
Lexer lexer;
ParserWrapper parser(&lexer);

BOOST_AUTO_TEST_CASE(compoBasicStructure) {
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
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "HTTPServer", "server", 7);
    
    // Check provision
    std::shared_ptr<nodes::compo::CProvision> provision = std::dynamic_pointer_cast<nodes::compo::CProvision>(descriptor->getBodyNodeAt(0)); 
    TEST_PROVISION(provision, nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    std::shared_ptr<nodes::compo::CRequirement> requirement = std::dynamic_pointer_cast<nodes::compo::CRequirement>(descriptor->getBodyNodeAt(1));
    TEST_REQUIREMENT(requirement, nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check provision
    provision = std::dynamic_pointer_cast<nodes::compo::CProvision>(descriptor->getBodyNodeAt(2)); 
    TEST_PROVISION(provision, nodes::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    requirement = std::dynamic_pointer_cast<nodes::compo::CRequirement>(descriptor->getBodyNodeAt(3));
    TEST_REQUIREMENT(requirement, nodes::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(4));
    TEST_SERVICE(service, "create", 0, 0, 0);
    
    // Check constraint
    std::shared_ptr<nodes::compo::CConstraint> constraint = std::dynamic_pointer_cast<nodes::compo::CConstraint>(descriptor->getBodyNodeAt(5));
    TEST_CONSTRAINT(constraint, "httpOnly", 0, 0);
    
    // Check architecture
    std::shared_ptr<nodes::compo::CArchitecture> architecture = std::dynamic_pointer_cast<nodes::compo::CArchitecture>(descriptor->getBodyNodeAt(6));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ARCHITECTURE, architecture->getNodeType());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceParams) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test {\
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
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(2));
    TEST_SERVICE(service, "twoparams", 2, 0, 0);
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(1))->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(3));
    TEST_SERVICE(service, "threeparams", 3, 0, 0);
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("param3", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getParamAt(2))->getStringValue());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceBody) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test {\
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
    input.str(
    "descriptor test {\
        service temporaries() {\
            | a b |\
            a;\
        }\
    }");
    
    // Parse input and create AST
    parser.parse(input);    
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "temporaries", 0, 1, 2);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getTemporaryAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getTemporaryAt(1));
    TEST_SYMBOL(symbol, "b");    
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoProvision) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test {\
	provides {\
		default : { run(a, b); stop(c) };\
                port1 : { start(a, b); close() };\
                port2 : IPrinting;\
                fE : FrontEnd;\
                bE : *;\
                handlers[] : RequestHandler;\
	}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check provision
    std::shared_ptr<nodes::compo::CProvision> provision = std::dynamic_pointer_cast<nodes::compo::CProvision>(descriptor->getBodyNodeAt(0)); 
    TEST_PROVISION(provision, nodes::types::visibilityType::EXTERNAL, 6);
    
    // Check port
    std::shared_ptr<nodes::compo::CSignaturesPort> signPort = std::dynamic_pointer_cast<nodes::compo::CSignaturesPort>(provision->getPortAt(0));
    TEST_SIGNATURES_PORT2(signPort, "default", "run", "stop");
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("c", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signPort->getSignatureAt(0)->getParamAt(0))->getStringValue());
    
    // Check port
    signPort = std::dynamic_pointer_cast<nodes::compo::CSignaturesPort>(provision->getPortAt(1));
    TEST_SIGNATURES_PORT2(signPort, "port1", "start", "close");
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    
    // Check port
    std::shared_ptr<nodes::compo::CNamedPort> namedPort = std::dynamic_pointer_cast<nodes::compo::CNamedPort>(provision->getPortAt(2));
    TEST_NAMED_PORT(namedPort, "port2", "IPrinting");
    
    // Check port
    namedPort = std::dynamic_pointer_cast<nodes::compo::CNamedPort>(provision->getPortAt(3));
    TEST_NAMED_PORT(namedPort, "fE", "FrontEnd");
    
    // Check port
    std::shared_ptr<nodes::compo::CUniversalPort> universalPort = std::dynamic_pointer_cast<nodes::compo::CUniversalPort>(provision->getPortAt(4));
    BOOST_CHECK_EQUAL("bE", universalPort->getName());
    
    // Check port
    namedPort = std::dynamic_pointer_cast<nodes::compo::CNamedPort>(provision->getPortAt(5));
    TEST_NAMED_PORT(namedPort, "handlers", "RequestHandler");
    BOOST_CHECK(namedPort->getCollectivity());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoArchitecture) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test {\
	architecture {\
            connect logger@analyzer to logging@logger;\
            connect outReqHa@analyzer to reqHa@handlers[i];\
            connect logger@&analyzer to logging@&logger;\
            disconnect logger@analyzer from logging@logger;\
	}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check architecture
    std::shared_ptr<nodes::compo::CArchitecture> architecture = std::dynamic_pointer_cast<nodes::compo::CArchitecture>(descriptor->getBodyNodeAt(0));
    TEST_ARCHITECTURE(architecture, 4);
    
    // Check bind node
    std::shared_ptr<nodes::compo::CDisconnection> disconnection = std::dynamic_pointer_cast<nodes::compo::CDisconnection>(architecture->getBodyNodeAt(0));
    TEST_DISCONNECTION(disconnection);
    
    // Check port address
    std::shared_ptr<nodes::compo::CPortAddress> portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(disconnection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(disconnection->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Check bind node
    std::shared_ptr<nodes::compo::CConnection> connection = std::dynamic_pointer_cast<nodes::compo::CConnection>(architecture->getBodyNodeAt(1));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification2());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logging", "logger");
    
    // Check bind node
    connection = std::dynamic_pointer_cast<nodes::compo::CConnection>(architecture->getBodyNodeAt(2));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "outReqHa", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("reqHa", portAddress->getPortName()->getStringValue());
    std::shared_ptr<nodes::compo::CCollectionPortLiteral> collectionPortLiteral = std::dynamic_pointer_cast<nodes::compo::CCollectionPortLiteral>(portAddress->getComponent());
    BOOST_CHECK_EQUAL("handlers", collectionPortLiteral->getPortName()->getStringValue());
    BOOST_CHECK_EQUAL("i", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(collectionPortLiteral->getIndexExpression())->getStringValue());
    
    // Check bind node
    connection = std::dynamic_pointer_cast<nodes::compo::CConnection>(architecture->getBodyNodeAt(3));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoServiceCall) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor test {\
	architecture {\
            connect handlers@self to default@(RequestHandler.new(handler.getName('a', 1, var, handler.getPtr())));\
	}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check architecture
    std::shared_ptr<nodes::compo::CArchitecture> architecture = std::dynamic_pointer_cast<nodes::compo::CArchitecture>(descriptor->getBodyNodeAt(0));
    TEST_ARCHITECTURE(architecture, 1);
    
    // Check bind node
    std::shared_ptr<nodes::compo::CConnection> connection = std::dynamic_pointer_cast<nodes::compo::CConnection>(architecture->getBodyNodeAt(0));
    TEST_CONNECTION(connection);
    
    // Check port address
    std::shared_ptr<nodes::compo::CPortAddress> portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "handlers", "self");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<nodes::compo::CPortAddress>(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("default", portAddress->getPortName()->getStringValue());
    std::shared_ptr<nodes::compo::CServiceInvocation> serviceInvocation = std::dynamic_pointer_cast<nodes::compo::CServiceInvocation>(portAddress->getComponent());
    BOOST_CHECK_EQUAL("RequestHandler", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("new", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    serviceInvocation = std::dynamic_pointer_cast<nodes::compo::CServiceInvocation>(serviceInvocation->getParameters());
    BOOST_CHECK_EQUAL("handler", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getName", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    std::shared_ptr<nodes::compo::CServiceSignature> signature = std::dynamic_pointer_cast<nodes::compo::CServiceSignature>(serviceInvocation->getParameters());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SERVICE_SIGNATURE, signature->getNodeType());
    BOOST_CHECK_EQUAL("getName", signature->getName());
    
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<nodes::procedural::CStringLiteral>(signature->getParamAt(0))->getValue());
    BOOST_CHECK_EQUAL(1, std::dynamic_pointer_cast<nodes::procedural::CConstant>(signature->getParamAt(1))->getValue());
    BOOST_CHECK_EQUAL("var", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(signature->getParamAt(2))->getStringValue());
    
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SERVICE_INVOCATION, std::dynamic_pointer_cast<nodes::CNode>(signature->getParamAt(3))->getNodeType());
    serviceInvocation = std::dynamic_pointer_cast<nodes::compo::CServiceInvocation>(signature->getParamAt(3));
    BOOST_CHECK_EQUAL("handler", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getPtr", std::dynamic_pointer_cast<nodes::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()