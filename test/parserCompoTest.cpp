#include <memory>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "testDefinitions.h"
#include "definitions.h"

BOOST_AUTO_TEST_SUITE(parserCompoTest)

// Global lexer and parser for testing purposes
ParserWrapper parser(new_ptr(Lexer)());

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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "HTTPServer", "server", 1, 1);
    
    // Check provision
    ptr(ast_provision) provision = cast(ast_provision)(descriptor->getExProvision());
    TEST_PROVISION(provision, ast::nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getNameSymbol()->getStringValue());
    
    // Check requirement
    ptr(ast_requirement) requirement = cast(ast_requirement)(descriptor->getExRequirement());
    TEST_REQUIREMENT(requirement, ast::nodes::types::visibilityType::EXTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getNameSymbol()->getStringValue());
    
    // Check provision
    provision = cast(ast_provision)(descriptor->getInProvision());
    TEST_PROVISION(provision, ast::nodes::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", provision->getPortAt(0)->getNameSymbol()->getStringValue());
    
    // Check requirement
    requirement = cast(ast_requirement)(descriptor->getInRequirement());
    TEST_REQUIREMENT(requirement, ast::nodes::types::visibilityType::INTERNAL, 1);
    BOOST_CHECK_EQUAL("default", requirement->getPortAt(0)->getNameSymbol()->getStringValue());
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "create", 0, 0, 0);
    
    // Check constraint
    ptr(ast_constraint) constraint = cast(ast_constraint)(descriptor->getConstraintAt(0));
    TEST_CONSTRAINT(constraint, "httpOnly", 0, 0);
    
    // Check architecture
    ptr(ast_architecture) architecture = cast(ast_architecture)(descriptor->getArchitecture());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::ARCHITECTURE, architecture->getNodeType());
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 4, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "noparams", 0, 0, 0);
    
    // Check service
    service = cast(ast_service)(descriptor->getServiceAt(1));
    TEST_SERVICE(service, "oneparam", 1, 0, 0);
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service->getParamAt(0))->getStringValue());
    
    // Check service
    service = cast(ast_service)(descriptor->getServiceAt(2));
    TEST_SERVICE(service, "twoparams", 2, 0, 0);
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(service->getParamAt(1))->getStringValue());
    
    // Check service
    service = cast(ast_service)(descriptor->getServiceAt(3));
    TEST_SERVICE(service, "threeparams", 3, 0, 0);
    BOOST_CHECK_EQUAL("param1", cast(ast_symbol)(service->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param2", cast(ast_symbol)(service->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("param3", cast(ast_symbol)(service->getParamAt(2))->getStringValue());
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 2, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "body1", 0, 1, 0);
    
    // Check symbol
    ptr(ast_symbol) symbol = cast(ast_symbol)(service->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check service
    service = cast(ast_service)(descriptor->getServiceAt(1));
    TEST_SERVICE(service, "body2", 0, 1, 0);
    
    // Check assignment
    ptr(ast_assignment) assignment = cast(ast_assignment)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(assignment->getRValue());
    TEST_CONSTANT(constant, 1);
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "temporaries", 0, 1, 2);
    
    // Check symbol
    ptr(ast_symbol) symbol = cast(ast_symbol)(service->getTemporaryAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Check symbol
    symbol = cast(ast_symbol)(service->getTemporaryAt(1));
    TEST_SYMBOL(symbol, "b");    
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check provision
    ptr(ast_provision) provision = cast(ast_provision)(descriptor->getExProvision()); 
    TEST_PROVISION(provision, ast::nodes::types::visibilityType::EXTERNAL, 6);
    
    // Check port
    ptr(ast_signaturesport) signPort = cast(ast_signaturesport)(provision->getPortAt(0));
    TEST_SIGNATURES_PORT2(signPort, "default", "run", "stop");
    BOOST_CHECK_EQUAL("a", cast(ast_symbol)(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", cast(ast_symbol)(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    BOOST_CHECK_EQUAL("c", cast(ast_symbol)(signPort->getSignatureAt(0)->getParamAt(0))->getStringValue());
    
    // Check port
    signPort = cast(ast_signaturesport)(provision->getPortAt(1));
    TEST_SIGNATURES_PORT2(signPort, "port1", "start", "close");
    BOOST_CHECK_EQUAL("a", cast(ast_symbol)(signPort->getSignatureAt(1)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("b", cast(ast_symbol)(signPort->getSignatureAt(1)->getParamAt(1))->getStringValue());
    
    // Check port
    ptr(ast_namedport) namedPort = cast(ast_namedport)(provision->getPortAt(2));
    TEST_NAMED_PORT(namedPort, "port2", "IPrinting");
    
    // Check port
    namedPort = cast(ast_namedport)(provision->getPortAt(3));
    TEST_NAMED_PORT(namedPort, "fE", "FrontEnd");
    
    // Check port
    ptr(ast_universalport) universalPort = cast(ast_universalport)(provision->getPortAt(4));
    BOOST_CHECK_EQUAL("bE", universalPort->getNameSymbol()->getStringValue());
    
    // Check port
    namedPort = cast(ast_namedport)(provision->getPortAt(5));
    TEST_NAMED_PORT(namedPort, "handlers", "RequestHandler");
    BOOST_CHECK(namedPort->getCollectivity());
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check architecture
    ptr(ast_architecture) architecture = cast(ast_architecture)(descriptor->getArchitecture());
    TEST_ARCHITECTURE(architecture, 5);
    
    // Check bind node
    ptr(ast_delegation) delegation = cast(ast_delegation)(architecture->getBodyNodeAt(0));
    TEST_DELEGATION(delegation);
    
    // Check port address
    ptr(ast_portaddress) portAddress = cast(ast_portaddress)(delegation->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = cast(ast_portaddress)(delegation->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Check bind node
    ptr(ast_disconnection) disconnection = cast(ast_disconnection)(architecture->getBodyNodeAt(1));
    TEST_DISCONNECTION(disconnection);
    
    // Check port address
    portAddress = cast(ast_portaddress)(disconnection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = cast(ast_portaddress)(disconnection->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Check bind node
    ptr(ast_connection) connection = cast(ast_connection)(architecture->getBodyNodeAt(2));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification1());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification2());
    TEST_PORT_ADDRES_DEREFERENCE(portAddress, "logging", "logger");
    
    // Check bind node
    connection = cast(ast_connection)(architecture->getBodyNodeAt(3));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "outReqHa", "analyzer");
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("reqHa", portAddress->getPortName()->getStringValue());
    ptr(ast_collectionportliteral) collectionPortLiteral = cast(ast_collectionportliteral)(portAddress->getComponent());
    BOOST_CHECK_EQUAL("handlers", collectionPortLiteral->getPortName()->getStringValue());
    BOOST_CHECK_EQUAL("i", cast(ast_symbol)(collectionPortLiteral->getIndexExpression())->getStringValue());
    
    // Check bind node
    connection = cast(ast_connection)(architecture->getBodyNodeAt(4));
    TEST_CONNECTION(connection);
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logger", "analyzer");
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification2());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "logging", "logger");
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 0);
    
    // Check architecture
    ptr(ast_architecture) architecture = cast(ast_architecture)(descriptor->getArchitecture());
    TEST_ARCHITECTURE(architecture, 1);
    
    // Check bind node
    ptr(ast_connection) connection = cast(ast_connection)(architecture->getBodyNodeAt(0));
    TEST_CONNECTION(connection);
    
    // Check port address
    ptr(ast_portaddress) portAddress = cast(ast_portaddress)(connection->getPortIdentification1());
    TEST_PORT_ADDRES_IDENTIFIER(portAddress, "handlers", "self");
    
    // Check port address
    portAddress = cast(ast_portaddress)(connection->getPortIdentification2());
    BOOST_CHECK_EQUAL("default", portAddress->getPortName()->getStringValue());
    
    ptr(ast_serviceinvocation) serviceInvocation = cast(ast_serviceinvocation)(portAddress->getComponent());
    BOOST_CHECK_EQUAL("RequestHandler", cast(ast_symbol)(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("new", cast(ast_symbol)(serviceInvocation->getSelectorName())->getStringValue());
    
    ptr(ast_servicesignature) signature = cast(ast_servicesignature)(serviceInvocation->getParameters());
    serviceInvocation = cast(ast_serviceinvocation)(signature->getParamAt(0));
    BOOST_CHECK_EQUAL("handler", cast(ast_symbol)(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getName", cast(ast_symbol)(serviceInvocation->getSelectorName())->getStringValue());
    
    signature = cast(ast_servicesignature)(serviceInvocation->getParameters());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::SERVICE_SIGNATURE, signature->getNodeType());
    BOOST_CHECK_EQUAL("getName", signature->getNameSymbol()->getStringValue());
    
    BOOST_CHECK_EQUAL("a", cast(ast_string)(signature->getParamAt(0))->getValue());
    BOOST_CHECK_EQUAL(1, cast(ast_constant)(signature->getParamAt(1))->getValue());
    BOOST_CHECK_EQUAL("var", cast(ast_symbol)(signature->getParamAt(2))->getStringValue());
    
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::SERVICE_INVOCATION, cast(ast::nodes::CNode)(signature->getParamAt(3))->getNodeType());
    serviceInvocation = cast(ast_serviceinvocation)(signature->getParamAt(3));
    BOOST_CHECK_EQUAL("handler", cast(ast_symbol)(serviceInvocation->getReceiverName())->getStringValue());
    BOOST_CHECK_EQUAL("getPtr", cast(ast_symbol)(serviceInvocation->getSelectorName())->getStringValue());
    
    // Clear AST for next test
    parser.clearAll();
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
    ptr(ast_interface) interface = cast(ast_interface)(parser.getRootNode()->getNodeAt(0));
    TEST_INTERFACE(interface, "IPrinting", "IAbcd", 2);
    
    // Check signature
    BOOST_CHECK_EQUAL("print", interface->getSignatureAt(1)->getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL("text", cast(ast_symbol)(interface->getSignatureAt(1)->getParamAt(0))->getStringValue());
    
    // Check signature
    BOOST_CHECK_EQUAL("printLn", interface->getSignatureAt(0)->getNameSymbol()->getStringValue());
    BOOST_CHECK_EQUAL("text", cast(ast_symbol)(interface->getSignatureAt(0)->getParamAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("param", cast(ast_symbol)(interface->getSignatureAt(0)->getParamAt(1))->getStringValue());
    
    // Clear AST for next test
    parser.clearAll();
}

BOOST_AUTO_TEST_SUITE_END()
