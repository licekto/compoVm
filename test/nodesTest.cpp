#include <iostream>

#include <boost/test/unit_test.hpp>

#include "nodes/procedural/symbol.h"
#include "nodes/compo/port.h"
#include "nodes/compo/requirement.h"
#include "nodes/compo/provision.h"
#include "nodes/compo/service.h"
#include "nodes/compo/constraint.h"
#include "nodes/compo/injectedPort.h"
#include "nodes/compo/descriptor.h"

BOOST_AUTO_TEST_SUITE(nodes)

BOOST_AUTO_TEST_CASE(compoSymbol) {
    // Original symbol creation
    nodes::procedural::CSymbol symbol("Symbol");
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    
    // Copy ctor test
    nodes::procedural::CSymbol symbolCopy1(symbol);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Copy assignment operator test
    nodes::procedural::CSymbol symbolCopy2 = symbol;
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbolCopy2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy2.getStringValue());
    
    // Move constructor test
    nodes::procedural::CSymbol symbolNew1(std::move(symbol));
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("", symbol.getStringValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Move assignment operator test
    nodes::procedural::CSymbol symbolNew2 = std::move(symbolNew1);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbolNew1.getNodeType());
    BOOST_CHECK_EQUAL("", symbolNew1.getStringValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SYMBOL, symbolNew2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolNew2.getStringValue());
}

BOOST_AUTO_TEST_CASE(compoPort) {
    // Original port creation
    nodes::compo::CPort port(new nodes::procedural::CSymbol("port"), true);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    
    // Copy ctor test
    nodes::compo::CPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy1.getName());
    BOOST_CHECK(portCopy1.getAtomic());
    
    // Copy assignment operator test
    nodes::compo::CPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy2.getName());
    BOOST_CHECK(portCopy2.getAtomic());
    
    // Move constructor test
    nodes::compo::CPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    
    // Move assignment operator test
    nodes::compo::CPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved2.getName());
    BOOST_CHECK(portMoved2.getAtomic());
}

BOOST_AUTO_TEST_CASE(compoInjectedPort) {
    // Original port creation
    nodes::compo::CInjectedPort port(new nodes::procedural::CSymbol("port"), true, new nodes::procedural::CSymbol("injectingPort"));
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::INJECTED_PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    
    // Copy ctor test
    nodes::compo::CInjectedPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portCopy1.getName());
    BOOST_CHECK(portCopy1.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portCopy1.getInjectedWith());
    
    // Copy assignment operator test
    nodes::compo::CInjectedPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portCopy2.getName());
    BOOST_CHECK(portCopy2.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portCopy2.getInjectedWith());
    
    // Move constructor test
    nodes::compo::CInjectedPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portMoved1.getInjectedWith());
    
    // Move assignment operator test
    nodes::compo::CInjectedPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("", portMoved1.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portMoved2.getName());
    BOOST_CHECK(portMoved2.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portMoved2.getInjectedWith());
}

BOOST_AUTO_TEST_CASE(compoProvision) {
    // Port vector preparation
    std::vector<nodes::compo::CPort*> portVec;
    portVec.push_back(new nodes::compo::CPort(new nodes::procedural::CSymbol("port1"), true));
    portVec.push_back(new nodes::compo::CPort(new nodes::procedural::CSymbol("port2"), false));
    
    // Original provision creation
    nodes::compo::CProvision provision(nodes::types::visibilityType::EXTERNAL, portVec);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provision.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName());
    BOOST_CHECK(provision.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName());
    BOOST_CHECK(!provision.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    nodes::compo::CProvision provisionCopy1(provision);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provisionCopy1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provisionCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionCopy1.getPortAt(1)->getName());
    
    // Assignment operator test
    nodes::compo::CProvision provisionCopy2 = provision;
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provisionCopy2.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provisionCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionCopy2.getPortAt(1)->getName());
    
    // Test of original provision
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provision.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName());
    
    nodes::compo::CProvision provisionNew1(std::move(provision));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provision.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionNew1.getPortAt(1)->getName());
    
    nodes::compo::CProvision provisionNew2 = std::move(provisionNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provisionNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::PROVISION, provisionNew2.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, provisionNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionNew2.getPortAt(1)->getName());
}

BOOST_AUTO_TEST_CASE(compoRequirement) {
    // Port vector preparation
    std::vector<nodes::compo::CPort*> portVec;
    portVec.push_back(new nodes::compo::CPort(new nodes::procedural::CSymbol("port1"), true));
    portVec.push_back(new nodes::compo::CPort(new nodes::procedural::CSymbol("port2"), false));
    
    // Original requirement creation
    nodes::compo::CRequirement requirement(nodes::types::visibilityType::EXTERNAL, portVec);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirement.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName());
    BOOST_CHECK(requirement.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName());
    BOOST_CHECK(!requirement.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    nodes::compo::CRequirement requirementCopy1(requirement);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirementCopy1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirementCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementCopy1.getPortAt(1)->getName());
    
    // Assignment operator test
    nodes::compo::CRequirement requirementCopy2 = requirement;
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirementCopy2.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirementCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementCopy2.getPortAt(1)->getName());
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirement.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName());
    
    nodes::compo::CRequirement requirementNew1(std::move(requirement));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirement.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementNew1.getPortAt(1)->getName());
    
    nodes::compo::CRequirement requirementNew2 = std::move(requirementNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirementNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::REQUIREMENT, requirementNew2.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::visibilityType::EXTERNAL, requirementNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementNew2.getPortAt(1)->getName());
}

BOOST_AUTO_TEST_CASE(compoService) {
    // Params vector preparation
    std::vector<nodes::procedural::CSymbol*> params;
    params.push_back(new nodes::procedural::CSymbol("param1"));
    params.push_back(new nodes::procedural::CSymbol("param2"));
    
    // Body vector preparation
    std::vector<nodes::CNode*> body;
    body.push_back(new nodes::procedural::CSymbol("Expr1"));
    
    // Temporaries vector preparation
    std::vector<nodes::CNode*> temporaries;
    temporaries.push_back(new nodes::procedural::CSymbol("Temp1"));
    
    // Service creation
    nodes::compo::CService service(new nodes::procedural::CSymbol("service"), params, body, temporaries);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Copy constructor test
    nodes::compo::CService serviceCopy1(service);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, serviceCopy1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy1.getName());
    BOOST_CHECK_EQUAL(2, serviceCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceCopy1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceCopy1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(serviceCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(serviceCopy1.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Copy assignment operator test
    nodes::compo::CService serviceCopy2 = service;
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, serviceCopy2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy2.getName());
    BOOST_CHECK_EQUAL(2, serviceCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceCopy2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceCopy2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(serviceCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(serviceCopy2.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Move constructor test
    nodes::compo::CService serviceNew1(std::move(service));
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew1.getName());
    BOOST_CHECK_EQUAL(2, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceNew1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceNew1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(serviceNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(serviceNew1.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("", service.getName());
    BOOST_CHECK_EQUAL(0, service.getParamsSize());
    BOOST_CHECK_EQUAL(0, service.getBodySize());
    BOOST_CHECK_EQUAL(0, service.getTemporariesSize());
    
    // Copy assignment operator test
    nodes::compo::CService serviceNew2 = std::move(serviceNew1);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, serviceNew2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew2.getName());
    BOOST_CHECK_EQUAL(2, serviceNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceNew2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceNew2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(serviceNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<nodes::procedural::CSymbol*>(serviceNew2.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL("", serviceNew1.getName());
    BOOST_CHECK_EQUAL(0, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getTemporariesSize());
}

BOOST_AUTO_TEST_CASE(compoConstraint) {
    // Params vector preparation
    std::vector<nodes::procedural::CSymbol*> params;
    params.push_back(new nodes::procedural::CSymbol("param1"));
    params.push_back(new nodes::procedural::CSymbol("param2"));
    
    // Body vector preparation
    std::vector<nodes::CNode*> body;
    body.push_back(new nodes::procedural::CSymbol("Expr1"));
    
    // Service creation
    nodes::compo::CConstraint constraint(new nodes::procedural::CSymbol("service"), params, body);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy constructor test
    nodes::compo::CConstraint constraintCopy1(constraint);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraintCopy1.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintCopy1.getName());
    BOOST_CHECK_EQUAL(2, constraintCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintCopy1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintCopy1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraintCopy1.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy assignment operator test
    nodes::compo::CConstraint constraingCopy2 = constraint;
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraingCopy2.getNodeType());
    BOOST_CHECK_EQUAL("service", constraingCopy2.getName());
    BOOST_CHECK_EQUAL(2, constraingCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraingCopy2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraingCopy2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraingCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraingCopy2.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Move constructor test
    nodes::compo::CConstraint constraintNew1(std::move(constraint));
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintNew1.getName());
    BOOST_CHECK_EQUAL(2, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintNew1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintNew1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraintNew1.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("", constraint.getName());
    BOOST_CHECK_EQUAL(0, constraint.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraint.getBodySize());
    
    // Copy assignment operator test
    nodes::compo::CConstraint constraintNew2 = std::move(constraintNew1);
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraintNew2.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintNew2.getName());
    BOOST_CHECK_EQUAL(2, constraintNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintNew2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintNew2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(constraintNew2.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(nodes::types::nodeTypeEnum::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL("", constraintNew1.getName());
    BOOST_CHECK_EQUAL(0, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraintNew1.getBodySize());
}

BOOST_AUTO_TEST_CASE(compoDescriptor) {
    // Descriptor body preparation
    std::vector<nodes::CNode*> body;
    body.push_back(new nodes::procedural::CSymbol("Expr1"));
    body.push_back(new nodes::procedural::CSymbol("Expr2"));
    
    // Descriptor creation
    nodes::compo::CDescriptor descriptor(new nodes::procedural::CSymbol("descriptorName"), new nodes::procedural::CSymbol("descriptorExtends"), body);
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Copy constructor test
    nodes::compo::CDescriptor descriptorCopy1(descriptor);
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptorCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptorCopy1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Copy assignment operator test
    nodes::compo::CDescriptor descriptorCopy2 = descriptor;
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptorCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptorCopy2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Move constructor test
    nodes::compo::CDescriptor descriptorNew1(std::move(descriptor));
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptorNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptorNew1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptor.getName());
    BOOST_CHECK_EQUAL("", descriptor.getExtends());
    BOOST_CHECK_EQUAL(0, descriptor.getBodySize());
    
    // Move assignment operator test
    nodes::compo::CDescriptor descriptorNew2 = std::move(descriptorNew1);
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<nodes::procedural::CSymbol*>(descriptorNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<nodes::procedural::CSymbol*>(descriptorNew2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(0, descriptorNew1.getBodySize());
}

BOOST_AUTO_TEST_SUITE_END()