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

BOOST_AUTO_TEST_CASE(interfaceComponentTest) {
    
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
    
    bool ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap->bootstrapStringValue("testType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", 1, ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), "testType");
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
