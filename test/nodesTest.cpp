#include <iostream>

#include <boost/test/unit_test.hpp>

#include "compoSymbol.h"
#include "compoPort.h"
#include "compoRequirement.h"
#include "compoProvision.h"

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
    BOOST_CHECK_EQUAL("port", port.getName()->getStringValue());
    BOOST_CHECK(port.getAtomic());
    
    // Copy ctor test
    compo::CCompoPort portCopy1(port);
    BOOST_CHECK_EQUAL("port", port.getName()->getStringValue());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy1.getName()->getStringValue());
    BOOST_CHECK(portCopy1.getAtomic());
    
    // Copy assignment operator test
    compo::CCompoPort portCopy2 = port;
    BOOST_CHECK_EQUAL("port", port.getName()->getStringValue());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portCopy2.getName()->getStringValue());
    BOOST_CHECK(portCopy2.getAtomic());
    
    // Move constructor test
    compo::CCompoPort portMoved1(std::move(port));
    BOOST_CHECK_EQUAL("", port.getName()->getStringValue());
    BOOST_CHECK(port.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved1.getName()->getStringValue());
    BOOST_CHECK(portMoved1.getAtomic());
    
    // Move assignment operator test
    compo::CCompoPort portMoved2 = std::move(portMoved1);
    BOOST_CHECK_EQUAL("", portMoved1.getName()->getStringValue());
    BOOST_CHECK(portMoved1.getAtomic());
    BOOST_CHECK_EQUAL("port", portMoved2.getName()->getStringValue());
    BOOST_CHECK(portMoved2.getAtomic());
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
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK(provision.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName()->getStringValue());
    BOOST_CHECK(!provision.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    compo::CCompoProvision provisionCopy1(provision);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionCopy1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy1.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", provisionCopy1.getPortAt(1)->getName()->getStringValue());
    
    // Assignment operator test
    compo::CCompoProvision provisionCopy2 = provision;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionCopy2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionCopy2.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", provisionCopy2.getPortAt(1)->getName()->getStringValue());
    
    // Test of original provision
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provision.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provision.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", provision.getPortAt(1)->getName()->getStringValue());
    
    compo::CCompoProvision provisionNew1(std::move(provision));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provision.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew1.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", provisionNew1.getPortAt(1)->getName()->getStringValue());
    
    compo::CCompoProvision provisionNew2 = std::move(provisionNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, provisionNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provisionNew2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provisionNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, provisionNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", provisionNew2.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", provisionNew2.getPortAt(1)->getName()->getStringValue());
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
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK(requirement.getPortAt(0)->getAtomic());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName()->getStringValue());
    BOOST_CHECK(!requirement.getPortAt(1)->getAtomic());
    
    // Copy constructor test
    compo::CCompoRequirement requirementCopy1(requirement);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementCopy1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementCopy1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy1.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", requirementCopy1.getPortAt(1)->getName()->getStringValue());
    
    // Assignment operator test
    compo::CCompoRequirement requirementCopy2 = requirement;
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementCopy2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementCopy2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementCopy2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementCopy2.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", requirementCopy2.getPortAt(1)->getName()->getStringValue());
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirement.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirement.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", requirement.getPortAt(1)->getName()->getStringValue());
    
    compo::CCompoRequirement requirementNew1(std::move(requirement));
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirement.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew1.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew1.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", requirementNew1.getPortAt(1)->getName()->getStringValue());
    
    compo::CCompoRequirement requirementNew2 = std::move(requirementNew1);
    
    // Test of original requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew1.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew1.getVisibilityType());
    BOOST_CHECK_EQUAL(0, requirementNew1.getNumberOfPorts());
    
    // Test of moved requirement
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirementNew2.getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirementNew2.getVisibilityType());
    BOOST_CHECK_EQUAL(2, requirementNew2.getNumberOfPorts());
    BOOST_CHECK_EQUAL("port1", requirementNew2.getPortAt(0)->getName()->getStringValue());
    BOOST_CHECK_EQUAL("port2", requirementNew2.getPortAt(1)->getName()->getStringValue());
}

BOOST_AUTO_TEST_SUITE_END()