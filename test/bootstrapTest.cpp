#include <iostream>
#include <memory>
#include <typeinfo>

#include <boost/test/unit_test.hpp>

#include "logger/logger.h"

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"
#include "types.h"
#include "definitions/interpreterDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "exceptions/runtime/wrongPortTypeException.h"

BOOST_AUTO_TEST_SUITE(bootstrapTest)

// Create parser, core modules, interpreter and bootstrap
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(core_modules) coreModules = new_ptr(core_modules)(parser);
ptr(core_bootstrap) bootstrap = new_ptr(core_bootstrap)(coreModules/*, interpreter*/);

BOOST_AUTO_TEST_CASE(componentTest) {
    // Bootstrap
    
    ptr(mem_component) owner;
    
    ptr(mem_component) component = bootstrap->bootstrapComponent(owner);
    
    TEST_COMPONENT(component, owner);
    
    BOOST_CHECK_THROW(component->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(component->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(valuesComponentsTest) {
    
    ptr(mem_string) stringComponent = bootstrap->bootstrapStringValue("test");
    
    BOOST_CHECK_EQUAL(stringComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(stringComponent->getDefaultPort()->getOwner().get(), stringComponent.get());
    BOOST_CHECK_EQUAL(stringComponent->getValue(), "test");
    
    ptr(mem_bool) boolComponent = bootstrap->bootstrapBoolValue(false);
    
    BOOST_CHECK_EQUAL(boolComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(boolComponent->getDefaultPort()->getOwner().get(), boolComponent.get());
    BOOST_CHECK_EQUAL(boolComponent->getValue(), false);
    
    ptr(mem_uint) uintComponent = bootstrap->bootstrapUIntValue(159456);
    
    BOOST_CHECK_EQUAL(uintComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(uintComponent->getDefaultPort()->getOwner().get(), uintComponent.get());
    BOOST_CHECK_EQUAL(uintComponent->getValue(), 159456);
}

BOOST_AUTO_TEST_CASE(serviceComponentTest) {
    std::vector<ptr(ast_node)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignature"), params);
    
    std::string codeStr = "1+1;";
    ptr(ast_string) code = new_ptr(ast_string)(codeStr);
    ptr(ast_service) serviceAst = new_ptr(ast_service)(signAst, code);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) service = bootstrap->bootstrapServiceComponent(serviceAst, owner);
    
    TEST_BASE_COMPONENT(service, 6, owner);
    BOOST_CHECK_EQUAL(cast(mem_string)(service->getPortByName("code")->getConnectedPortAt(0)->getOwner())->getValue(), codeStr);
    
    BOOST_CHECK_THROW(service->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(service->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(serviceSignatureComponentTest) {
    
    std::vector<ptr(ast_node)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignature"), params);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) signatureComponent = bootstrap->bootstrapServiceSignatureComponent(signAst, owner);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(signatureComponent->getParent(), 10, owner);
    TEST_PRIMITIVE_PORT(signatureComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testSignature");
    TEST_PRIMITIVE_PORT(signatureComponent, "paramNames", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("paramNames")->getConnectedPortsNumber(), 2);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("paramNames")->getConnectedPortAt(0)->getOwner())->getValue(), "param1");
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("paramNames")->getConnectedPortAt(1)->getOwner())->getValue(), "param2");

    bool ret = false;
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testSignatureTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "setSelector", 1, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testSignatureTest");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getSelector", 0, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getServiceByName("getSelector")->invoke()->getOwner())->getValue(), "testSignatureTest");
    
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamsCount", 0, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_uint)(signatureComponent->getServiceByName("getParamsCount")->invoke()->getOwner())->getValue(), 2);
    
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", 1, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param1");
    
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(1)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", 1, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param2");
    
    ret = false;
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(0)->getDefaultPort());
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("param3")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "setParamName", 2, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    signatureComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", 1, ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param3");
    
    BOOST_CHECK_THROW(signatureComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(signatureComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(namedInterfaceComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPort");
    bool atomicity = false;
    bool collectivity = false;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
    
    ptr(ast_namedport) astPort = new_ptr(ast_namedport)(portName, atomicity, collectivity, visibility, role, componentName);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) interfaceComponent = bootstrap->bootstrapInterfaceComponent(astPort, owner, nullptr);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(interfaceComponent->getParent(), 16, owner);
    
    TEST_PRIMITIVE_PORT(interfaceComponent, "type", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), PORT_TYPE_NAMED);
    TEST_PRIMITIVE_PORT(interfaceComponent, "componentName", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("componentName")->getConnectedPortAt(0)->getOwner())->getValue(), "testComponent");
    TEST_PRIMITIVE_PORT(interfaceComponent, "signatures", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("signatures")->getConnectedPortsNumber(), 0);
    TEST_PRIMITIVE_PORT(interfaceComponent, "component", types::roleType::REQUIRES, types::visibilityType::EXTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("component")->getConnectedPortsNumber(), 0);
    TEST_PRIMITIVE_PORT(interfaceComponent, "services", types::roleType::REQUIRES, types::visibilityType::EXTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("services")->getConnectedPortsNumber(), 0);
    
    bool ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), PORT_TYPE_NAMED);
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), "testType");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testType");
    
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignaturesCount", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_uint)(retPort->getOwner())->getValue(), 0);
    
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getConnectedComponentName", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testComponent");
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testComponentTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setConnectedComponentName", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("componentName")->getConnectedPortAt(0)->getOwner())->getValue(), "testComponentTest");
    
    BOOST_CHECK_THROW(interfaceComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(interfaceComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(signatureInterfaceComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPort");
    bool atomicity = false;
    bool collectivity = false;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
    
    std::vector<ptr(ast_servicesignature)> signatures;
    
    for (size_t i = 0; i < 3; ++i) {
        std::vector<ptr(ast_node)> params;
        
        std::string name = "param_" + std::to_string(i) + "1";
        params.push_back(new_ptr(ast_symbol)(name));
        name = "param_" + std::to_string(i) + "2";
        params.push_back(new_ptr(ast_symbol)(name));

        name = "signature" + std::to_string(i);
        ptr(ast_servicesignature) signature = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)(name), params);
        
        signatures.push_back(signature);
    }
    
    ptr(ast_signaturesport) astPort = new_ptr(ast_signaturesport)(portName, atomicity, collectivity, visibility, role, signatures);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) interfaceComponent = bootstrap->bootstrapInterfaceComponent(astPort, owner, nullptr);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(interfaceComponent->getParent(), 16, owner);
    
    TEST_PRIMITIVE_PORT(interfaceComponent, "type", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), PORT_TYPE_SIGNATURES);
    TEST_PRIMITIVE_PORT(interfaceComponent, "componentName", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("componentName")->getConnectedPortsNumber(), 0);
    TEST_PRIMITIVE_PORT(interfaceComponent, "signatures", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("signatures")->getConnectedPortsNumber(), 3);
    TEST_PRIMITIVE_PORT(interfaceComponent, "component", types::roleType::REQUIRES, types::visibilityType::EXTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("component")->getConnectedPortsNumber(), 0);
    TEST_PRIMITIVE_PORT(interfaceComponent, "services", types::roleType::REQUIRES, types::visibilityType::EXTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("services")->getConnectedPortsNumber(), 0);
    
    bool ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), PORT_TYPE_SIGNATURES);
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), "testType");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testType");
    
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignaturesCount", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_uint)(retPort->getOwner())->getValue(), 3);
    
    BOOST_CHECK_THROW(interfaceComponent->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getConnectedComponentName")->getPrimitiveService()->invoke(),
            exceptions::runtime::CWrongPortTypeException);
    
    ret = true;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "signature0");
    
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(1)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "signature1");
    
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(2)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "signature2");
    
    std::vector<ptr(ast_node)> params;
        
    std::string name = "param_31";
    params.push_back(new_ptr(ast_symbol)(name));
    name = "param_32";
    params.push_back(new_ptr(ast_symbol)(name));

    name = "signature3";
    ptr(ast_servicesignature) signature = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)(name), params);
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapServiceSignatureComponent(signature, interfaceComponent)->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "addSignature", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(3)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "signature3");
    
    BOOST_CHECK_THROW(interfaceComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(interfaceComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(portComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPort");
    bool atomicity = false;
    bool collectivity = false;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
            
    ptr(ast_namedport) astPort = new_ptr(ast_namedport)(portName, atomicity, collectivity, visibility, role, componentName);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) portComponent = bootstrap->bootstrapPortComponent(astPort, owner);
    
    TEST_BASE_COMPONENT(portComponent->getParent(), 12, owner);
    
    TEST_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
    
    ptr(mem_port) retPort;
    bool ret = true;
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "getName", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testPort");
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "getInterface", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner()->getPortByName("type")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), PORT_TYPE_NAMED);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("componentName")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "testComponent");
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isConnected", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), false);
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isDelegated", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), false);
    
    ptr(mem_component) connectedComponent = bootstrap->bootstrapComponent(nullptr);
    
    ret = false;
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    connectedComponent = bootstrap->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    
    BOOST_CHECK_THROW(portComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(portComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(collectionPortComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPort");
    bool atomicity = false;
    bool collectivity = true;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
            
    ptr(ast_namedport) astPort = new_ptr(ast_namedport)(portName, atomicity, collectivity, visibility, role, componentName);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) portComponent = bootstrap->bootstrapCollectionPortComponent(astPort, owner);
    
    TEST_BASE_COMPONENT(portComponent->getParent(), 13, owner);
    
    TEST_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
    
    ptr(mem_component) connectedComponent = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    connectedComponent = bootstrap->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(1)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    
    connectedComponent = bootstrap->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(2)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 3);
    
    portComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(2)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    
    portComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(1)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    portComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    
    BOOST_CHECK_THROW(portComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(portComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(portDescriptionComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPortDescription");
    bool atomicity = false;
    bool collectivity = false;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
            
    ptr(ast_namedport) astPort = new_ptr(ast_namedport)(portName, atomicity, collectivity, visibility, role, componentName);
    astPort->setKindOf(new_ptr(ast_symbol)("SuperPort"));
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) portDescriptionComponent = bootstrap->bootstrapPortDescriptionComponent(astPort, owner);
    
    TEST_BASE_COMPONENT(portDescriptionComponent->getParent(), 17, owner);
    
    TEST_PRIMITIVE_PORT(portDescriptionComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portDescriptionComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPortDescription");
    TEST_PRIMITIVE_PORT(portDescriptionComponent, "role", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portDescriptionComponent->getPortByName("role")->getConnectedPortAt(0)->getOwner())->getValue(), ROLE_PROVISION);
    TEST_PRIMITIVE_PORT(portDescriptionComponent, "visibility", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portDescriptionComponent->getPortByName("visibility")->getConnectedPortAt(0)->getOwner())->getValue(), VISIBILITY_EXTERNAL);
    TEST_PRIMITIVE_PORT(portDescriptionComponent, "kind", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portDescriptionComponent->getPortByName("kind")->getConnectedPortAt(0)->getOwner())->getValue(), "SuperPort");
    TEST_PRIMITIVE_PORT(portDescriptionComponent, "isCollectionPort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(portDescriptionComponent->getPortByName("isCollectionPort")->getConnectedPortAt(0)->getOwner())->getValue(), false);
    
    ptr(mem_port) retPort;
    
    bool ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testPortDescriptionTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setName", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getName", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testPortDescriptionTest");
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "testPortDescriptionTest");
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue(ROLE_REQUIREMENT)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setRole", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getRole", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), ROLE_REQUIREMENT);
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), ROLE_REQUIREMENT);
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("SelfPort")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setKind", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getKind", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "SelfPort");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "SelfPort");
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue(VISIBILITY_INTERNAL)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setVisibility", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getVisibility", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), VISIBILITY_INTERNAL);
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), VISIBILITY_INTERNAL);
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapBoolValue(true)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setIsCollection", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "isCollection", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), true);
    ptr(mem_bool) boolVal = cast(mem_bool)(retPort->getOwner());
    BOOST_CHECK_EQUAL(boolVal->getValue(), true);
    
    ret = false;
    ptr(mem_component) intf = bootstrap->bootstrapInterfaceComponent(astPort, owner, nullptr);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(intf->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setInterface", 1, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getInterface", 0, ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(retPort->getOwner().get(), intf->getParent().get());
    
    BOOST_CHECK_THROW(portDescriptionComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(portDescriptionComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(connectionDescriptionComponentTest) {
    ptr(ast_portaddress) addr1 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("default"), new_ptr(ast_symbol)("backend"));
    ptr(ast_portaddress) addr2 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("self"), new_ptr(ast_symbol)("frontend"));
    
    ptr(ast_connection) astConnection = new_ptr(ast_connection)(addr1, addr2);
        
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) connectionDescriptionComponent = bootstrap->bootstrapConnectionDescriptionComponent(astConnection, owner);
    
    TEST_BASE_COMPONENT(connectionDescriptionComponent->getParent(), 15, owner);
    
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourceComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "backend");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourcePort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourcePort")->getConnectedPortAt(0)->getOwner())->getValue(), "default");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "frontend");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationPort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationPort")->getConnectedPortAt(0)->getOwner())->getValue(), "self");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "isDisconnection", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(connectionDescriptionComponent->getPortByName("isDisconnection")->getConnectedPortAt(0)->getOwner())->getValue(), false);
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("newBackend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourceComponent", 1, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourceComponent", 0, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newBackend");
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newBackend");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("newDefault")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourcePort", 1, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourcePort", 0, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newDefault");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newDefault");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("newFrontend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationComponent", 1, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationComponent", 0, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newFrontend");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newFrontend");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("newSelf")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationPort", 1, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationPort", 0, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newSelf");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newSelf");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap->bootstrapBoolValue(true)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setIsDisconnection", 1, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "isDisconnection", 0, ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), true);
    ptr(mem_bool) boolVal = cast(mem_bool)(retPort->getOwner());
    BOOST_CHECK_EQUAL(boolVal->getValue(), true);
    
    BOOST_CHECK_THROW(connectionDescriptionComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(connectionDescriptionComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_SUITE_END()
