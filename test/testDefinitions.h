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

#define TEST_BOOL(boolean, val) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::BOOLEAN, boolean->getNodeType()); \
    BOOST_CHECK_EQUAL(val, boolean->getValue()); \
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
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, connection->getSourcePortIdentification()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, connection->getDestinationPortIdentification()->getNodeType()); \
} while(0)

#define TEST_DISCONNECTION(disconnection) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::DISCONNECTION, disconnection->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, disconnection->getSourcePortIdentification()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, disconnection->getDestinationPortIdentification()->getNodeType()); \
} while(0)

#define TEST_DELEGATION(delegation) \
do { \
    BOOST_CHECK_EQUAL(types::nodeType::DELEGATION, delegation->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, delegation->getSourcePortIdentification()->getNodeType()); \
    BOOST_CHECK_EQUAL(types::nodeType::PORT_ADDRESS, delegation->getDestinationPortIdentification()->getNodeType()); \
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

#define TEST_PRIMITIVE_PORT(component, portName, role, visibility, connectedServices) \
do { \
    BOOST_CHECK(component->getPortByName(portName)->isPrimitive()); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getName(), portName); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getOwner().get(), component.get()); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getRole(), role); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getVisibility(), visibility); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getPrimitivePort()->getConnectedServicesNumber(), connectedServices); \
} while(0)

#define TEST_PRIMITIVE_SERVICE(component, portName, serviceName, ret, retPort) \
do { \
    BOOST_CHECK(component->getPortByName(portName)->getPrimitivePort()->getConnectedServiceByName(serviceName)->isPrimitive()); \
    BOOST_CHECK_EQUAL(component->getPortByName(portName)->getPrimitivePort()->getConnectedServiceByName(serviceName)->getName(), serviceName); \
    retPort = component->getPortByName(portName)->getPrimitivePort()->getConnectedServiceByName(serviceName)->getPrimitiveService()->invoke(); \
    if (ret) { \
        BOOST_CHECK(retPort.use_count()); \
    } \
    else { \
        BOOST_CHECK(!retPort.use_count()); \
    } \
} while(0)

#define TEST_BASE_COMPONENT_PRIMITIVE(component, servicesTotal, owner, bootstrap1) \
do { \
    ptr(mem_port) _retPort_; \
    TEST_PRIMITIVE_PORT(component, "default", types::roleType::PROVIDES, types::visibilityType::EXTERNAL, servicesTotal); \
    TEST_PRIMITIVE_SERVICE(component, "default", "getPorts", false, _retPort_); \
    ptr(mem_string) strComp = bootstrap1->bootstrapStringValue("default"); \
    component->getPortByName("args")->connectPort(strComp->getDefaultPort()); \
    TEST_PRIMITIVE_SERVICE(component, "default", "getPortNamed", true, _retPort_); \
    BOOST_CHECK_EQUAL(component->getPortByName("args")->getConnectedPortsNumber(), 0); \
    TEST_PRIMITIVE_SERVICE(component, "default", "getDescriptor", false, _retPort_); \
    TEST_PRIMITIVE_SERVICE(component, "default", "getIdentityHash", true, _retPort_); \
    if (owner.get()) { \
        TEST_PRIMITIVE_SERVICE(component, "default", "getOwner", true, _retPort_); \
        BOOST_CHECK_EQUAL(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getOwner")->getPrimitiveService()->invoke().get(), owner->getPortByName("default").get()); \
    } \
    TEST_PRIMITIVE_PORT(component, "self", types::roleType::PROVIDES, types::visibilityType::INTERNAL, servicesTotal); \
} while(0)

#define TEST_COMPONENT_PRIMITIVE(component, owner, bootstrap1) \
do { \
    TEST_BASE_COMPONENT_PRIMITIVE(component, 5, owner, bootstrap1); \
} while(0)

#define TEST_PORT_COMPONENT(port, name, connectedPorts) \
do { \
    BOOST_CHECK(port->getPortByName("default")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("args")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("owner")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("descriptorPort")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("self")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("super")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("connectedPorts")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("delegatedPorts")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("name")->isPrimitive()); \
    BOOST_CHECK(port->getPortByName("interfaceDescription")->isPrimitive()); \
    BOOST_CHECK_EQUAL(port->getPortByName("default")->getPrimitivePort()->getConnectedServicesNumber(), 13); \
    BOOST_CHECK_EQUAL(port->getPortByName("default")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("args")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("args")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("owner")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("owner")->getPrimitivePort()->getConnectedPortsNumber(), 1); \
    BOOST_CHECK_EQUAL(port->getPortByName("descriptorPort")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("descriptorPort")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("self")->getPrimitivePort()->getConnectedServicesNumber(), 13); \
    BOOST_CHECK_EQUAL(port->getPortByName("self")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("super")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("super")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("connectedPorts")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("connectedPorts")->getPrimitivePort()->getConnectedPortsNumber(), connectedPorts); \
    BOOST_CHECK_EQUAL(port->getPortByName("delegatedPorts")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("delegatedPorts")->getPrimitivePort()->getConnectedPortsNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("name")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("name")->getPrimitivePort()->getConnectedPortsNumber(), 1); \
    BOOST_CHECK_EQUAL(cast(mem_string)(port->getPortByName("name")->getPrimitivePort()->getConnectedPortAt(0)->getOwner())->getValue(), name); \
    BOOST_CHECK_EQUAL(port->getPortByName("interfaceDescription")->getPrimitivePort()->getConnectedServicesNumber(), 0); \
    BOOST_CHECK_EQUAL(port->getPortByName("interfaceDescription")->getPrimitivePort()->getConnectedPortsNumber(), 1); \
} while(0)

#define TEST_BASE_COMPONENT_COMPONENT(component, descriptorConnected) \
do { \
    std::string portName = "default"; \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, 0); \
    portName = "args"; \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, 0); \
    portName = "owner"; \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, 0); \
    portName = "descriptorPort"; \
    int _connectedPorts_ = 0; \
    if (descriptorConnected) { \
        _connectedPorts_ = 1; \
    } \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, _connectedPorts_); \
    portName = "super"; \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, 0); \
    portName = "self"; \
    BOOST_CHECK(!component->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(component->getPortByName(portName)->getPort(), portName, 0); \
} while(0)

#define TEST_DESCRIPTOR_COMPONENT(descriptorComponent, name, extends, portsNumber, servicesNumber, bindNumber) \
do { \
    BOOST_CHECK_EQUAL(descriptorComponent->getNumberOfPorts(), 11); \
    BOOST_CHECK_EQUAL(descriptorComponent->getNumberOfAllServices(), 20); \
    TEST_BASE_COMPONENT_COMPONENT(descriptorComponent, false); \
    std::string portName = "name"; \
    BOOST_CHECK(!descriptorComponent->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(descriptorComponent->getPortByName(portName)->getPort(), portName, 1); \
    BOOST_CHECK_EQUAL(cast(mem_string)(descriptorComponent->getPortByName(portName)->getConnectedPortAt(0)->getOwner())->getValue(), name); \
    portName = "parentName"; \
    BOOST_CHECK(!descriptorComponent->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(descriptorComponent->getPortByName(portName)->getPort(), portName, 1); \
    std::string extendsName = extends; \
    if (extendsName == "") { \
        extendsName = "Component"; \
    } \
    BOOST_CHECK_EQUAL(cast(mem_string)(descriptorComponent->getPortByName(portName)->getConnectedPortAt(0)->getOwner())->getValue(), extendsName); \
    portName = "ports"; \
    BOOST_CHECK(!descriptorComponent->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(descriptorComponent->getPortByName(portName)->getPort(), portName, portsNumber); \
    BOOST_CHECK_EQUAL(descriptorComponent->getPortByName(portName)->getConnectedPortsNumber(), portsNumber); \
    portName = "architectureDefinition"; \
    BOOST_CHECK(!descriptorComponent->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(descriptorComponent->getPortByName(portName)->getPort(), portName, bindNumber); \
    BOOST_CHECK_EQUAL(descriptorComponent->getPortByName(portName)->getConnectedPortsNumber(), bindNumber); \
    portName = "services"; \
    BOOST_CHECK(!descriptorComponent->getPortByName(portName)->isPrimitive()); \
    TEST_PORT_COMPONENT(descriptorComponent->getPortByName(portName)->getPort(), portName, servicesNumber); \
    BOOST_CHECK_EQUAL(descriptorComponent->getPortByName(portName)->getConnectedPortsNumber(), servicesNumber); \
} while(0)
