#include <iostream>

#include <boost/test/unit_test.hpp>

#include "nodes/proceduralNodes/compoSymbol.h"
#include "nodes/compoNodes/compoPort.h"
#include "nodes/compoNodes/compoRequirement.h"
#include "nodes/compoNodes/compoProvision.h"
#include "nodes/compoNodes/compoService.h"
#include "nodes/compoNodes/compoConstraint.h"
#include "nodes/compoNodes/compoInjectedPort.h"
#include "nodes/compoNodes/compoDescriptor.h"

BOOST_AUTO_TEST_SUITE(nodes)

BOOST_AUTO_TEST_CASE(compoSymbol) {
    // Original symbol creation
    compo::CCompoSymbol symbol("Symbol");
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    
    // Copy ctor test
    compo::CCompoSymbol symbolCopy1(symbol);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Copy assignment operator test
    compo::CCompoSymbol symbolCopy2 = symbol;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbol.getStringValue());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbolCopy2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy2.getStringValue());
    
    // Move constructor test
    compo::CCompoSymbol symbolNew1(std::move(symbol));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbol.getNodeType());
    BOOST_CHECK_EQUAL("", symbol.getStringValue());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbolCopy1.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolCopy1.getStringValue());
    
    // Move assignment operator test
    compo::CCompoSymbol symbolNew2 = std::move(symbolNew1);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbolNew1.getNodeType());
    BOOST_CHECK_EQUAL("", symbolNew1.getStringValue());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, symbolNew2.getNodeType());
    BOOST_CHECK_EQUAL("Symbol", symbolNew2.getStringValue());
}

BOOST_AUTO_TEST_CASE(compoPort) {
    // Original port creation
    compo::CCompoPort port(new compo::CCompoSymbol("port"), true);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    
    // Copy ctor test
    compo::CCompoPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy1.getName());
    BOOST_CHECK(portCopy1.getAtomic());
    
    // Copy assignment operator test
    compo::CCompoPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy2.getName());
    BOOST_CHECK(portCopy2.getAtomic());
    
    // Move constructor test
    compo::CCompoPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    
    // Move assignment operator test
    compo::CCompoPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved2.getName());
    BOOST_CHECK(portMoved2.getAtomic());
}

BOOST_AUTO_TEST_CASE(compoInjectedPort) {
    // Original port creation
    compo::CCompoInjectedPort port(new compo::CCompoSymbol("port"), true, new compo::CCompoSymbol("injectingPort"));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::INJECTED_PORT, port.getNodeType());
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    
    // Copy ctor test
    compo::CCompoInjectedPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portCopy1.getName());
    BOOST_CHECK(portCopy1.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portCopy1.getInjectedWith());
    
    // Copy assignment operator test
    compo::CCompoInjectedPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portCopy2.getName());
    BOOST_CHECK(portCopy2.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portCopy2.getInjectedWith());
    
    // Move constructor test
    compo::CCompoInjectedPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("", port.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portMoved1.getInjectedWith());
    
    // Move assignment operator test
    compo::CCompoInjectedPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("", portMoved1.getInjectedWith());
    BOOST_CHECK_EQUAL("port", portMoved2.getName());
    BOOST_CHECK(portMoved2.getAtomic());
    BOOST_CHECK_EQUAL("injectingPort", portMoved2.getInjectedWith());
}

BOOST_AUTO_TEST_CASE(compoProvision) {
    // Port vector preparation
    std::vector<compo::CCompoPort*> portVec;
    portVec.push_back(new compo::CCompoPort(new compo::CCompoSymbol("port1"), true));
    portVec.push_back(new compo::CCompoPort(new compo::CCompoSymbol("port2"), false));
    
    // Original provision creation
    compo::CCompoProvision provision(compo::visibilityType::EXTERNAL, portVec);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provision.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName());
    BOOST_CHECK(provision.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName());
    BOOST_CHECK(!provision.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    compo::CCompoProvision provisionCopy1(provision);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionCopy1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionCopy1.getPortAt(1)->getName());
    
    // Assignment operator test
    compo::CCompoProvision provisionCopy2 = provision;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionCopy2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionCopy2.getPortAt(1)->getName());
    
    // Test of original provision
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provision.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName());
    
    compo::CCompoProvision provisionNew1(std::move(provision));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provision.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionNew1.getPortAt(1)->getName());
    
    compo::CCompoProvision provisionNew2 = std::move(provisionNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provisionNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", provisionNew2.getPortAt(1)->getName());
}

BOOST_AUTO_TEST_CASE(compoRequirement) {
    // Port vector preparation
    std::vector<compo::CCompoPort*> portVec;
    portVec.push_back(new compo::CCompoPort(new compo::CCompoSymbol("port1"), true));
    portVec.push_back(new compo::CCompoPort(new compo::CCompoSymbol("port2"), false));
    
    // Original requirement creation
    compo::CCompoRequirement requirement(compo::visibilityType::EXTERNAL, portVec);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirement.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName());
    BOOST_CHECK(requirement.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName());
    BOOST_CHECK(!requirement.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    compo::CCompoRequirement requirementCopy1(requirement);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementCopy1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementCopy1.getPortAt(1)->getName());
    
    // Assignment operator test
    compo::CCompoRequirement requirementCopy2 = requirement;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementCopy2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementCopy2.getPortAt(1)->getName());
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirement.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName());
    
    compo::CCompoRequirement requirementNew1(std::move(requirement));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirement.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew1.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementNew1.getPortAt(1)->getName());
    
    compo::CCompoRequirement requirementNew2 = std::move(requirementNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirementNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew2.getPortAt(0)->getName());
    BOOST_CHECK_EQUAL("port2", requirementNew2.getPortAt(1)->getName());
}

BOOST_AUTO_TEST_CASE(compoService) {
    // Params vector preparation
    std::vector<compo::CCompoSymbol*> params;
    params.push_back(new compo::CCompoSymbol("param1"));
    params.push_back(new compo::CCompoSymbol("param2"));
    
    // Body vector preparation
    std::vector<compo::CCompoNode*> body;
    body.push_back(new compo::CCompoSymbol("Expr1"));
    
    // Temporaries vector preparation
    std::vector<compo::CCompoNode*> temporaries;
    temporaries.push_back(new compo::CCompoSymbol("Temp1"));
    
    // Service creation
    compo::CCompoService service(new compo::CCompoSymbol("service"), params, body, temporaries);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Copy constructor test
    compo::CCompoService serviceCopy1(service);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, serviceCopy1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy1.getName());
    BOOST_CHECK_EQUAL(2, serviceCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceCopy1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceCopy1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(serviceCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(serviceCopy1.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Copy assignment operator test
    compo::CCompoService serviceCopy2 = service;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, serviceCopy2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceCopy2.getName());
    BOOST_CHECK_EQUAL(2, serviceCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceCopy2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceCopy2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(serviceCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceCopy2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(serviceCopy2.getTemporaryAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("service", service.getName());
    BOOST_CHECK_EQUAL(2, service.getParamsSize());
    BOOST_CHECK_EQUAL("param1", service.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", service.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(service.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, service.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(service.getTemporaryAt(0))->getStringValue());
    
    // Move constructor test
    compo::CCompoService serviceNew1(std::move(service));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew1.getName());
    BOOST_CHECK_EQUAL(2, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceNew1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceNew1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(serviceNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew1.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(serviceNew1.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service.getNodeType());
    BOOST_CHECK_EQUAL("", service.getName());
    BOOST_CHECK_EQUAL(0, service.getParamsSize());
    BOOST_CHECK_EQUAL(0, service.getBodySize());
    BOOST_CHECK_EQUAL(0, service.getTemporariesSize());
    
    // Copy assignment operator test
    compo::CCompoService serviceNew2 = std::move(serviceNew1);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, serviceNew2.getNodeType());
    BOOST_CHECK_EQUAL("service", serviceNew2.getName());
    BOOST_CHECK_EQUAL(2, serviceNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", serviceNew2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", serviceNew2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(serviceNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL(1, serviceNew2.getTemporariesSize());
    BOOST_CHECK_EQUAL("Temp1", dynamic_cast<compo::CCompoSymbol*>(serviceNew2.getTemporaryAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, serviceNew1.getNodeType());
    BOOST_CHECK_EQUAL("", serviceNew1.getName());
    BOOST_CHECK_EQUAL(0, serviceNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getBodySize());
    BOOST_CHECK_EQUAL(0, serviceNew1.getTemporariesSize());
}

BOOST_AUTO_TEST_CASE(compoConstraint) {
    // Params vector preparation
    std::vector<compo::CCompoSymbol*> params;
    params.push_back(new compo::CCompoSymbol("param1"));
    params.push_back(new compo::CCompoSymbol("param2"));
    
    // Body vector preparation
    std::vector<compo::CCompoNode*> body;
    body.push_back(new compo::CCompoSymbol("Expr1"));
    
    // Service creation
    compo::CCompoConstraint constraint(new compo::CCompoSymbol("service"), params, body);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy constructor test
    compo::CCompoConstraint constraintCopy1(constraint);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraintCopy1.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintCopy1.getName());
    BOOST_CHECK_EQUAL(2, constraintCopy1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintCopy1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintCopy1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraintCopy1.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Copy assignment operator test
    compo::CCompoConstraint constraingCopy2 = constraint;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraingCopy2.getNodeType());
    BOOST_CHECK_EQUAL("service", constraingCopy2.getName());
    BOOST_CHECK_EQUAL(2, constraingCopy2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraingCopy2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraingCopy2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraingCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraingCopy2.getBodyNodeAt(0))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("service", constraint.getName());
    BOOST_CHECK_EQUAL(2, constraint.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraint.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraint.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraint.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraint.getBodyNodeAt(0))->getStringValue());
    
    // Move constructor test
    compo::CCompoConstraint constraintNew1(std::move(constraint));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintNew1.getName());
    BOOST_CHECK_EQUAL(2, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintNew1.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintNew1.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraintNew1.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint.getNodeType());
    BOOST_CHECK_EQUAL("", constraint.getName());
    BOOST_CHECK_EQUAL(0, constraint.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraint.getBodySize());
    
    // Copy assignment operator test
    compo::CCompoConstraint constraintNew2 = std::move(constraintNew1);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraintNew2.getNodeType());
    BOOST_CHECK_EQUAL("service", constraintNew2.getName());
    BOOST_CHECK_EQUAL(2, constraintNew2.getParamsSize());
    BOOST_CHECK_EQUAL("param1", constraintNew2.getParamAt(0)->getStringValue());
    BOOST_CHECK_EQUAL("param2", constraintNew2.getParamAt(1)->getStringValue());
    BOOST_CHECK_EQUAL(1, constraintNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(constraintNew2.getBodyNodeAt(0))->getStringValue());
    // Check if original object is emptied
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraintNew1.getNodeType());
    BOOST_CHECK_EQUAL("", constraintNew1.getName());
    BOOST_CHECK_EQUAL(0, constraintNew1.getParamsSize());
    BOOST_CHECK_EQUAL(0, constraintNew1.getBodySize());
}

BOOST_AUTO_TEST_CASE(compoDescriptor) {
    // Descriptor body preparation
    std::vector<compo::CCompoNode*> body;
    body.push_back(new compo::CCompoSymbol("Expr1"));
    body.push_back(new compo::CCompoSymbol("Expr2"));
    
    // Descriptor creation
    compo::CCompoDescriptor descriptor(new compo::CCompoSymbol("descriptorName"), new compo::CCompoSymbol("descriptorExtends"), body);
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Copy constructor test
    compo::CCompoDescriptor descriptorCopy1(descriptor);
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptorCopy1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptorCopy1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Copy assignment operator test
    compo::CCompoDescriptor descriptorCopy2 = descriptor;
    BOOST_CHECK_EQUAL("descriptorName", descriptorCopy2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorCopy2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorCopy2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptorCopy2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptorCopy2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("descriptorName", descriptor.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptor.getExtends());
    BOOST_CHECK_EQUAL(2, descriptor.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptor.getBodyNodeAt(1))->getStringValue());
    
    // Move constructor test
    compo::CCompoDescriptor descriptorNew1(std::move(descriptor));
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew1.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptorNew1.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptorNew1.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptor.getName());
    BOOST_CHECK_EQUAL("", descriptor.getExtends());
    BOOST_CHECK_EQUAL(0, descriptor.getBodySize());
    
    // Move assignment operator test
    compo::CCompoDescriptor descriptorNew2 = std::move(descriptorNew1);
    BOOST_CHECK_EQUAL("descriptorName", descriptorNew2.getName());
    BOOST_CHECK_EQUAL("descriptorExtends", descriptorNew2.getExtends());
    BOOST_CHECK_EQUAL(2, descriptorNew2.getBodySize());
    BOOST_CHECK_EQUAL("Expr1", dynamic_cast<compo::CCompoSymbol*>(descriptorNew2.getBodyNodeAt(0))->getStringValue());
    BOOST_CHECK_EQUAL("Expr2", dynamic_cast<compo::CCompoSymbol*>(descriptorNew2.getBodyNodeAt(1))->getStringValue());
    // Check if original object remains untouched
    BOOST_CHECK_EQUAL("", descriptorNew1.getName());
    BOOST_CHECK_EQUAL("", descriptorNew1.getExtends());
    BOOST_CHECK_EQUAL(0, descriptorNew1.getBodySize());
}

BOOST_AUTO_TEST_SUITE_END()