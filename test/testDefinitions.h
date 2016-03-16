#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "ast/compo/descriptor.h"
#include "ast/compo/service.h"
#include "ast/procedural/assignmentExpression.h"
#include "ast/procedural/constant.h"

#define TEST_DESCRIPTOR(descriptor, name, extends, servicesSize, constraintsSize) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::DESCRIPTOR, descriptor->getNodeType()); \
    BOOST_CHECK_EQUAL(name, descriptor->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(extends, descriptor->getExtends()); \
    BOOST_CHECK_EQUAL("default", descriptor->getDefaultPort()->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(servicesSize, descriptor->getServicesSize()); \
    BOOST_CHECK_EQUAL(constraintsSize, descriptor->getConstraintsSize()); \
} while(0)

#define TEST_INTERFACE(interface, name, extends, signaturesListSize) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::INTERFACE, interface->getNodeType()); \
    BOOST_CHECK_EQUAL(name, interface->getName()->getStringValue()); \
    BOOST_CHECK_EQUAL(extends, interface->getExtends()->getStringValue()); \
    BOOST_CHECK_EQUAL(signaturesListSize, interface->getSignaturesSize()); \
} while(0)

#define TEST_PROVISION(provision, visibility, numOfPorts) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PROVISION, provision->getNodeType()); \
    BOOST_CHECK_EQUAL(visibility, provision->getVisibilityType()); \
    BOOST_CHECK_EQUAL(numOfPorts, provision->getNumberOfPorts()); \
} while(0)

#define TEST_REQUIREMENT(requirement, visibility, numOfPorts) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::REQUIREMENT, requirement->getNodeType()); \
    BOOST_CHECK_EQUAL(visibility, requirement->getVisibilityType()); \
    BOOST_CHECK_EQUAL(numOfPorts, requirement->getNumberOfPorts()); \
} while(0)

#define TEST_SERVICE(service, name, numOfParams, bodySize, temporariesSize) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::SERVICE, service->getNodeType()); \
    BOOST_CHECK_EQUAL(name, service->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(numOfParams, service->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, service->getBodySize()); \
    BOOST_CHECK_EQUAL(temporariesSize, service->getTemporariesSize()); \
} while(0)

#define TEST_CONSTRAINT(service, name, numOfParams, bodySize) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTRAINT, constraint->getNodeType()); \
    BOOST_CHECK_EQUAL(name, constraint->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(numOfParams, constraint->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, constraint->getBodySize()); \
} while(0)

#define TEST_SYMBOL(symbol, name) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::SYMBOL, symbol->getNodeType()); \
    BOOST_CHECK_EQUAL(name, symbol->getStringValue()); \
} while(0)

#define TEST_CONSTANT(constant, val) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, constant->getNodeType()); \
    BOOST_CHECK_EQUAL(val, constant->getValue()); \
} while(0)

#define TEST_SIGNATURES_PORT2(signPort, portName, sign1Name, sign2Name) \
do { \
    BOOST_CHECK_EQUAL(portName, signPort->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(sign1Name, signPort->getSignatureAt(1)->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(sign2Name, signPort->getSignatureAt(0)->getNameSymbol()->getStringValue()); \
} while(0)

#define TEST_NAMED_PORT(namedPort, portName, paramName) \
do { \
    BOOST_CHECK_EQUAL(portName, namedPort->getNameSymbol()->getStringValue()); \
    TEST_SYMBOL(namedPort->getParamName(), paramName); \
} while(0)

#define TEST_ARCHITECTURE(architecture, bodySize) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::ARCHITECTURE, architecture->getNodeType()); \
    BOOST_CHECK_EQUAL(bodySize, architecture->getBodySize()); \
} while(0)

#define TEST_CONNECTION(connection) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONNECTION, connection->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, connection->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, connection->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_DISCONNECTION(disconnection) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::DISCONNECTION, disconnection->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, disconnection->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, disconnection->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_DELEGATION(delegation) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::DELEGATION, delegation->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, delegation->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, delegation->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_PORT_ADDRES_DEREFERENCE(portAddress, portName, componentName) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, portAddress->getNodeType()); \
    TEST_SYMBOL(portAddress->getPortName(), portName); \
    TEST_SYMBOL(std::dynamic_pointer_cast<ast::compo::CDereferenceLiteral>(portAddress->getComponent())->getParamName(), componentName); \
} while(0)

#define TEST_PORT_ADDRES_IDENTIFIER(portAddress, portName, componentName) \
do { \
    BOOST_CHECK_EQUAL(ast::types::nodeType::PORT_ADDRESS, portAddress->getNodeType()); \
    TEST_SYMBOL(portAddress->getPortName(), portName); \
    TEST_SYMBOL(std::dynamic_pointer_cast<ast::procedural::CSymbol>(portAddress->getComponent()), componentName); \
} while(0)
