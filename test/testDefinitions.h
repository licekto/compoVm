#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "ast/nodes/compo/descriptor.h"
#include "ast/nodes/compo/service.h"
#include "ast/nodes/procedural/assignmentExpression.h"
#include "ast/nodes/procedural/constant.h"

#define TEST_DESCRIPTOR(descriptor, name, extends, portsSize, servicesSize, constraintsSize) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::DESCRIPTOR, descriptor->getNodeType()); \
    BOOST_CHECK_EQUAL(name, descriptor->getNameSymbol()->getStringValue()); \
    if (descriptor->getExtendsSymbol()) { \
        BOOST_CHECK_EQUAL(extends, descriptor->getExtendsSymbol()->getStringValue()); \
    } \
    std::string extendsStr = extends; \
    if (!descriptor->getExtendsSymbol() && !extendsStr.empty()) { \
        BOOST_CHECK(0); \
    } \
    BOOST_CHECK_EQUAL(portsSize, descriptor->getPortsSize()); \
    BOOST_CHECK_EQUAL(servicesSize, descriptor->getServicesSize()); \
    BOOST_CHECK_EQUAL(constraintsSize, descriptor->getConstraintsSize()); \
} while(0)

#define TEST_INTERFACE(interface, name, extends, signaturesListSize) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::INTERFACE, interface->getNodeType()); \
    BOOST_CHECK_EQUAL(name, interface->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(extends, interface->getExtendsSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(signaturesListSize, interface->getSignaturesSize()); \
} while(0)

#define TEST_SERVICE(service, name, numOfParams, bodySize, temporariesSize) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::SERVICE, service->getNodeType()); \
    BOOST_CHECK_EQUAL(name, service->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(numOfParams, service->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, service->getBodySize()); \
    BOOST_CHECK_EQUAL(temporariesSize, service->getTemporariesSize()); \
} while(0)

#define TEST_CONSTRAINT(service, name, numOfParams, bodySize) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::CONSTRAINT, constraint->getNodeType()); \
    BOOST_CHECK_EQUAL(name, constraint->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(numOfParams, constraint->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, constraint->getBodySize()); \
} while(0)

#define TEST_SYMBOL(symbol, name) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::SYMBOL, symbol->getNodeType()); \
    BOOST_CHECK_EQUAL(name, symbol->getStringValue()); \
} while(0)

#define TEST_CONSTANT(constant, val) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::CONSTANT, constant->getNodeType()); \
    BOOST_CHECK_EQUAL(val, constant->getValue()); \
} while(0)

#define TEST_PORT(signPort, portName, visibility, role) \
do { \
    BOOST_CHECK_EQUAL(portName, signPort->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(visibility, signPort->getVisibility()); \
    BOOST_CHECK_EQUAL(role, signPort->getRole()); \
} while(0)

#define TEST_SIGNATURES_PORT2(signPort, portName, visibility, role, sign1Name, sign2Name) \
do { \
    TEST_PORT(signPort, portName, visibility, role); \
    BOOST_CHECK_EQUAL(sign1Name, signPort->getSignatureAt(1)->getNameSymbol()->getStringValue()); \
    BOOST_CHECK_EQUAL(sign2Name, signPort->getSignatureAt(0)->getNameSymbol()->getStringValue()); \
} while(0)

#define TEST_NAMED_PORT(namedPort, portName, visibility, role, paramName) \
do { \
    TEST_PORT(namedPort, portName, visibility, role); \
    BOOST_CHECK_EQUAL(portName, namedPort->getNameSymbol()->getStringValue()); \
    TEST_SYMBOL(namedPort->getComponentName(), paramName); \
} while(0)

#define TEST_ARCHITECTURE(architecture, bodySize) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::ARCHITECTURE, architecture->getNodeType()); \
    BOOST_CHECK_EQUAL(bodySize, architecture->getBodySize()); \
} while(0)

#define TEST_CONNECTION(connection) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::CONNECTION, connection->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, connection->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, connection->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_DISCONNECTION(disconnection) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::DISCONNECTION, disconnection->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, disconnection->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, disconnection->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_DELEGATION(delegation) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::DELEGATION, delegation->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, delegation->getPortIdentification1()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, delegation->getPortIdentification2()->getNodeType()); \
} while(0)

#define TEST_PORT_ADDRES_DEREFERENCE(portAddress, portName, componentName) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, portAddress->getNodeType()); \
    TEST_SYMBOL(portAddress->getPortName(), portName); \
    TEST_SYMBOL(std::dynamic_pointer_cast<ast::nodes::compo::CDereferenceLiteral>(portAddress->getComponent())->getParamName(), componentName); \
} while(0)

#define TEST_PORT_ADDRES_IDENTIFIER(portAddress, portName, componentName) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, portAddress->getNodeType()); \
    TEST_SYMBOL(portAddress->getPortName(), portName); \
    TEST_SYMBOL(std::dynamic_pointer_cast<ast::nodes::procedural::CSymbol>(portAddress->getComponent()), componentName); \
} while(0)
