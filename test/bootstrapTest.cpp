#include <iostream>
#include <memory>
#include <typeinfo>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"
#include "types.h"
#include "definitions/interpreterDefinitions.h"
#include "definitions/memoryObjectsDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"

BOOST_AUTO_TEST_SUITE(bootstrapTest)

// Create parser, core modules, interpreter and bootstrap
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());
ptr(core_modules) coreModules = new_ptr(core_modules)(parser);
ptr(core_interpreter) interpreter = new_ptr(core_interpreter)(parser, coreModules);
ptr(core_bootstrap) bootstrap = new_ptr(core_bootstrap)(coreModules, interpreter);

BOOST_AUTO_TEST_CASE(componentTest) {
    // Bootstrap
    
    ptr(mem_component) owner;
    
    ptr(mem_component) component = bootstrap->bootstrapComponent(owner);
    
    TEST_COMPONENT(component, owner);
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

BOOST_AUTO_TEST_CASE(serviceSignatureComponentTest) {
    
    std::vector<ptr(ast_node)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignature"), params);
    
    ptr(mem_component) owner = bootstrap->bootstrapComponent(nullptr);
    
    ptr(mem_component) signatureComponent = bootstrap->bootstrapServiceSignatureComponent(signAst, owner);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(signatureComponent, 10, owner);
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
    
    ptr(mem_component) interfaceComponent = bootstrap->bootstrapInterfaceComponent(astPort, owner);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(interfaceComponent, 12, owner);
    
    TEST_PRIMITIVE_PORT(interfaceComponent, "type", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), PORT_TYPE_NAMED);
    TEST_PRIMITIVE_PORT(interfaceComponent, "connectedComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("connectedComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "testComponent");
    TEST_PRIMITIVE_PORT(interfaceComponent, "signatures", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("signatures")->getConnectedPortsNumber(), 0);
    
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
    
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getConnectedComponent", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testComponent");
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testComponentTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setConnectedComponent", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("connectedComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "testComponentTest");
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
    
    ptr(mem_component) interfaceComponent = bootstrap->bootstrapInterfaceComponent(astPort, owner);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT(interfaceComponent, 12, owner);
    
    TEST_PRIMITIVE_PORT(interfaceComponent, "type", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), PORT_TYPE_SIGNATURES);
    TEST_PRIMITIVE_PORT(interfaceComponent, "connectedComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("connectedComponent")->getConnectedPortsNumber(), 0);
    TEST_PRIMITIVE_PORT(interfaceComponent, "signatures", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("signatures")->getConnectedPortsNumber(), 3);
    
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
    
    ret = false;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getConnectedComponent", 0, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(retPort.use_count(), 0);
    
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
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setSignature", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapUIntValue(3)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("name")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "signature3");
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
    
    TEST_BASE_COMPONENT(portComponent, 12, owner);
    
    TEST_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
}

BOOST_AUTO_TEST_SUITE_END()
