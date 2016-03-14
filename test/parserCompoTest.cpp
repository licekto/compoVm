#include <memory>

#include <boost/test/unit_test.hpp>

#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "ast/compo/descriptor.h"
#include "ast/compo/provision.h"
#include "ast/compo/requirement.h"
#include "ast/compo/service.h"
#include "ast/compo/constraint.h"
#include "ast/compo/architecture.h"
#include "ast/compo/namedPort.h"
#include "ast/compo/universalPort.h"
#include "ast/compo/connection.h"
#include "ast/compo/disconnection.h"
#include "ast/compo/delegation.h"
#include "ast/compo/dereferenceLiteral.h"
#include "ast/compo/serviceInvocation.h"
#include "ast/compo/collectionPortLiteral.h"
#include "ast/procedural/stringLiteral.h"
#include "ast/procedural/parens.h"
#include "ast/compo/interface.h"

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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "HTTPServer", "server", 1, 1);
    
    // Check provision
    std::shared_ptr<ast::compo::CProvision> provision = std::dynamic_pointer_cast<ast::compo::CProvision>(descriptor->getExProvision());
    TEST_PROVISION(provision, ast::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    std::shared_ptr<ast::compo::CRequirement> requirement = std::dynamic_pointer_cast<ast::compo::CRequirement>(descriptor->getExRequirement());
    TEST_REQUIREMENT(requirement, ast::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check provision
    provision = std::dynamic_pointer_cast<ast::compo::CProvision>(descriptor->getInProvision());
    TEST_PROVISION(provision, ast::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getName());
    
    // Check requirement
    requirement = std::dynamic_pointer_cast<ast::compo::CRequirement>(descriptor->getInRequirement());
    TEST_REQUIREMENT(requirement, ast::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getName());
    
    // Check service
    std::shared_ptr<ast::compo::CService> service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "create", 0, 0, 0);
    
    // Check constraint
    std::shared_ptr<ast::compo::CConstraint> constraint = std::dynamic_pointer_cast<ast::compo::CConstraint>(descriptor->getConstraintAt(0));
    TEST_CONSTRAINT(constraint, "httpOnly", 0, 0);
    
    // Check architecture
    std::shared_ptr<ast::compo::CArchitecture> architecture = std::dynamic_pointer_cast<ast::compo::CArchitecture>(descriptor->getArchitecture());
    BOOST_CHECK_EQUAL(ast::types::nodeType::ARCHITECTURE, architecture->getNodeType());
    
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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 4, 0);
    
    // Check service
    std::shared_ptr<ast::compo::CService> service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "noparams", 0, 0, 0);
    
    // Check service
    service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(1));
    TEST_SERVICE(service, "oneparam", 1, 0, 0);
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(2));
    TEST_SERVICE(service, "twoparams", 2, 0, 0);
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(1))->getStringValue());
    
    // Check service
    service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(3));
    TEST_SERVICE(service, "threeparams", 3, 0, 0);
    BOOST_CHECK_EQUAL("param1", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("param3", std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getParamAt(2))->getStringValue());
    
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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 2, 0);
    
    // Check service
    std::shared_ptr<ast::compo::CService> service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "body1", 0, 1, 0);
    
    // Check symbol
    std::shared_ptr<ast::procedural::CSymbol> symbol = std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check service
    service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(1));
    TEST_SERVICE(service, "body2", 0, 1, 0);
    
    // Check assignment
    std::shared_ptr<ast::procedural::CAssignmentExpression> assignment = std::dynamic_pointer_cast<ast::procedural::CAssignmentExpression>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(ast::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<ast::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    // Check constant
    std::shared_ptr<ast::procedural::CConstant> constant = std::dynamic_pointer_cast<ast::procedural::CConstant>(assignment->getRValue());
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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1, 0);
    
    // Check service
    std::shared_ptr<ast::compo::CService> service = std::dynamic_pointer_cast<ast::compo::CService>(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "temporaries", 0, 1, 2);
    
    // Check symbol
    std::shared_ptr<ast::procedural::CSymbol> symbol = std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getTemporaryAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<ast::procedural::CSymbol>(service->getTemporaryAt(1));
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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check provision
    std::shared_ptr<ast::compo::CProvision> provision = std::dynamic_pointer_cast<ast::compo::CProvision>(descriptor->getExProvision()); 
    TEST_PROVISION(provision, ast::types::visibilityType::EXTERNAL, 6);
    
    // Check port
    std::shared_ptr<ast::compo::CSignaturesPort> signPort = std::dynamic_pointer_cast<ast::compo::CSignaturesPort>(provision->getPortAt(0));
    TEST_SIGNATURES_PORT2(signPort, "default", "run", "stop");
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("c", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signPort->getSignatureAt(0)->getParamAt(0))->getStringValue());
    
    // Check port
    signPort = std::dynamic_pointer_cast<ast::compo::CSignaturesPort>(provision->getPortAt(1));
    TEST_SIGNATURES_PORT2(signPort, "port1", "start", "close");
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    
    // Check port
    std::shared_ptr<ast::compo::CNamedPort> namedPort = std::dynamic_pointer_cast<ast::compo::CNamedPort>(provision->getPortAt(2));
    TEST_NAMED_PORT(namedPort, "port2", "IPrinting");
    
    // Check port
    namedPort = std::dynamic_pointer_cast<ast::compo::CNamedPort>(provision->getPortAt(3));
    TEST_NAMED_PORT(namedPort, "fE", "FrontEnd");
    
    // Check port
    std::shared_ptr<ast::compo::CUniversalPort> universalPort = std::dynamic_pointer_cast<ast::compo::CUniversalPort>(provision->getPortAt(4));
    BOOST_CHECK_EQUAL("bE", universalPort->getName());
    
    // Check port
    namedPort = std::dynamic_pointer_cast<ast::compo::CNamedPort>(provision->getPortAt(5));
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
            delegate logger@analyzer to logging@logger;\
	}\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check architecture
    std::shared_ptr<ast::compo::CArchitecture> architecture = std::dynamic_pointer_cast<ast::compo::CArchitecture>(descriptor->getArchitecture());
    TEST_ARCHITECTURE(architecture, 5);
    
    // Check bind node
    std::shared_ptr<ast::compo::CDelegation> delegation = std::dynamic_pointer_cast<ast::compo::CDelegation>(architecture->getBodyNodeAt(0));
    TEST_DELEGATION(delegation);
    
    // Check port address
    std::shared_ptr<ast::compo::CPortAddress> portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(delegation->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(delegation->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Check bind node
    std::shared_ptr<ast::compo::CDisconnection> disconnection = std::dynamic_pointer_cast<ast::compo::CDisconnection>(architecture->getBodyNodeAt(1));
    TEST_DISCONNECTION(disconnection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(disconnection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(disconnection->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Check bind node
    std::shared_ptr<ast::compo::CConnection> connection = std::dynamic_pointer_cast<ast::compo::CConnection>(architecture->getBodyNodeAt(2));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification2());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logging", "logger");
    
    // Check bind node
    connection = std::dynamic_pointer_cast<ast::compo::CConnection>(architecture->getBodyNodeAt(3));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "outReqHa", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("reqHa", portAddress->getPortName()->getStringValue());
    std::shared_ptr<ast::compo::CCollectionPortLiteral> collectionPortLiteral = std::dynamic_pointer_cast<ast::compo::CCollectionPortLiteral>(portAddress->getComponent());
    BOOST_CHECK_EQUAL("handlers", collectionPortLiteral->getPortName()->getStringValue());
    BOOST_CHECK_EQUAL("i", std::dynamic_pointer_cast<ast::procedural::CSymbol>(collectionPortLiteral->getIndexExpression())->getStringValue());
    
    // Check bind node
    connection = std::dynamic_pointer_cast<ast::compo::CConnection>(architecture->getBodyNodeAt(4));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification2());
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
    std::shared_ptr<ast::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<ast::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check architecture
    std::shared_ptr<ast::compo::CArchitecture> architecture = std::dynamic_pointer_cast<ast::compo::CArchitecture>(descriptor->getArchitecture());
    TEST_ARCHITECTURE(architecture, 1);
    
    // Check bind node
    std::shared_ptr<ast::compo::CConnection> connection = std::dynamic_pointer_cast<ast::compo::CConnection>(architecture->getBodyNodeAt(0));
    TEST_CONNECTION(connection);
    
    // Check port address
    std::shared_ptr<ast::compo::CPortAddress> portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "handlers", "self");
    
    // Check port address
    portAddress = std::dynamic_pointer_cast<ast::compo::CPortAddress>(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("default", portAddress->getPortName()->getStringValue());
    
    std::shared_ptr<ast::compo::CServiceInvocation> serviceInvocation = std::dynamic_pointer_cast<ast::compo::CServiceInvocation>(portAddress->getComponent());
    BOOST_CHECK_EQUAL("RequestHandler", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("new", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    std::shared_ptr<ast::compo::CServiceSignature> signature = std::dynamic_pointer_cast<ast::compo::CServiceSignature>(serviceInvocation->getParameters());
    serviceInvocation = std::dynamic_pointer_cast<ast::compo::CServiceInvocation>(signature->getParamAt(0));
    BOOST_CHECK_EQUAL("handler", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getName", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    signature = std::dynamic_pointer_cast<ast::compo::CServiceSignature>(serviceInvocation->getParameters());
    BOOST_CHECK_EQUAL(ast::types::nodeType::SERVICE_SIGNATURE, signature->getNodeType());
    BOOST_CHECK_EQUAL("getName", signature->getName()->getStringValue());
    
    BOOST_CHECK_EQUAL("a", std::dynamic_pointer_cast<ast::procedural::CStringLiteral>(signature->getParamAt(0))->getValue());
    BOOST_CHECK_EQUAL(1, std::dynamic_pointer_cast<ast::procedural::CConstant>(signature->getParamAt(1))->getValue());
    BOOST_CHECK_EQUAL("var", std::dynamic_pointer_cast<ast::procedural::CSymbol>(signature->getParamAt(2))->getStringValue());
    
    BOOST_CHECK_EQUAL(ast::types::nodeType::SERVICE_INVOCATION, std::dynamic_pointer_cast<ast::CNode>(signature->getParamAt(3))->getNodeType());
    serviceInvocation = std::dynamic_pointer_cast<ast::compo::CServiceInvocation>(signature->getParamAt(3));
    BOOST_CHECK_EQUAL("handler", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getPtr", std::dynamic_pointer_cast<ast::procedural::CSymbol>(serviceInvocation->getSelectorName())->getStringValue());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoInterface) {
    // Testing input
    std::stringstream input;
    input.str(
    "interface IPrinting extends IAbcd {\
        print(text);\
        printLn(text, param);\
    }");
    
    // Parse input and create AST
    parser.parse(input);
    
    // Check interface
    std::shared_ptr<ast::compo::CInterface> interface = std::dynamic_pointer_cast<ast::compo::CInterface>(parser.getRootNodeAt(0));
    TEST_INTERFACE(interface, "IPrinting", "IAbcd", 2);
    
    // Check signature
    BOOST_CHECK_EQUAL("print", interface->getSignatureAt(1)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("text", std::dynamic_pointer_cast<ast::procedural::CSymbol>(interface->getSignatureAt(1)->getParamAt(0))->getStringValue());
    
    // Check signature
    BOOST_CHECK_EQUAL("printLn", interface->getSignatureAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("text", std::dynamic_pointer_cast<ast::procedural::CSymbol>(interface->getSignatureAt(0)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param", std::dynamic_pointer_cast<ast::procedural::CSymbol>(interface->getSignatureAt(0)->getParamAt(1))->getStringValue());
    
    // Clear AST for next test
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()
