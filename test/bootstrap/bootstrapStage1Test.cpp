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
#include "interpreter/core/bootstrap/bootstrapStage1.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"
#include "exceptions/runtime/wrongPortTypeException.h"

BOOST_AUTO_TEST_SUITE(bootstrapStage1Test)

// Create parser, core modules, interpreter and bootstrap
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(core_modules) coreModules = new_ptr(core_modules)(parser);
ptr(interpreter::memory::memspace::CMemory) memory = new_ptr(interpreter::memory::memspace::CMemory)();
ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(coreModules, nullptr, memory);

BOOST_AUTO_TEST_CASE(componentTest) {
    // Bootstrap
    
    ptr(mem_component) owner;
    
    ptr(mem_component) component = bootstrap1->bootstrapComponent(owner);
    
    TEST_COMPONENT_PRIMITIVE(component, owner, bootstrap1);
    
    BOOST_CHECK_THROW(component->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(component->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(valuesComponentsTest) {
    
    ptr(mem_string) stringComponent = bootstrap1->bootstrapStringValue("test");
    
    BOOST_CHECK_EQUAL(stringComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(stringComponent->getDefaultPort()->getOwner().get(), stringComponent.get());
    BOOST_CHECK_EQUAL(stringComponent->getValue(), "test");
    
    ptr(mem_bool) boolComponent = bootstrap1->bootstrapBoolValue(false);
    
    BOOST_CHECK_EQUAL(boolComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(boolComponent->getDefaultPort()->getOwner().get(), boolComponent.get());
    BOOST_CHECK_EQUAL(boolComponent->getValue(), false);
    
    ptr(mem_int) intComponent = bootstrap1->bootstrapIntValue(159456);
    
    BOOST_CHECK_EQUAL(intComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(intComponent->getDefaultPort()->getOwner().get(), intComponent.get());
    BOOST_CHECK_EQUAL(intComponent->getValue(), 159456);
    
    intComponent = bootstrap1->bootstrapIntValue(-54854698);
    
    BOOST_CHECK_EQUAL(intComponent->getDefaultPort()->getName(), "default");
    BOOST_CHECK_EQUAL(intComponent->getDefaultPort()->getOwner().get(), intComponent.get());
    BOOST_CHECK_EQUAL(intComponent->getValue(), -54854698);
}

BOOST_AUTO_TEST_CASE(serviceComponentTest) {
    std::vector<ptr(ast_node)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignature"), params);
    
    std::string codeStr = "{ |a| a := 1 + 5; a := false; a := \"hello\";}";
    ptr(ast_string) code = new_ptr(ast_string)(codeStr);
    ptr(ast_service) serviceAst = new_ptr(ast_service)(signAst, code);
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) service = bootstrap1->bootstrapServiceComponent(serviceAst, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(service, 6, owner, bootstrap1);
    ptr(mem_string) strComp = cast(mem_string)(service->getPortByName("code")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(strComp->getValue(), codeStr);
    
    BOOST_CHECK_EQUAL(service->getPortByName("tempsN")->getConnectedPortsNumber(), 1);
    BOOST_CHECK_EQUAL(cast(mem_string)(service->getPortByName("tempsN")->getConnectedPortAt(0)->getOwner())->getValue(), "a");
    
    BOOST_CHECK_EQUAL(service->getPortByName("tempsV")->getConnectedPortsNumber(), 4);
    BOOST_CHECK_EQUAL(cast(mem_int)(service->getPortByName("tempsV")->getConnectedPortAt(0)->getOwner())->getValue(), 1);
    BOOST_CHECK_EQUAL(cast(mem_int)(service->getPortByName("tempsV")->getConnectedPortAt(1)->getOwner())->getValue(), 5);
    BOOST_CHECK_EQUAL(cast(mem_bool)(service->getPortByName("tempsV")->getConnectedPortAt(2)->getOwner())->getValue(), false);
    BOOST_CHECK_EQUAL(cast(mem_string)(service->getPortByName("tempsV")->getConnectedPortAt(3)->getOwner())->getValue(), "hello");
    
    BOOST_CHECK_THROW(service->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(service->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(serviceSignatureComponentTest) {
    
    std::vector<ptr(ast_node)> params;
    params.push_back(new_ptr(ast_symbol)("param1"));
    params.push_back(new_ptr(ast_symbol)("param2"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignature"), params);
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) signatureComponent = bootstrap1->bootstrapServiceSignatureComponent(signAst, owner);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT_PRIMITIVE(signatureComponent->getParent(), 10, owner, bootstrap1);
    TEST_PRIMITIVE_PORT(signatureComponent, "selector", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSignature");
    TEST_PRIMITIVE_PORT(signatureComponent, "paramNames", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("paramNames")->getConnectedPortsNumber(), 2);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("paramNames")->getConnectedPortAt(0)->getOwner())->getValue(), "param1");
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("paramNames")->getConnectedPortAt(1)->getOwner())->getValue(), "param2");

    bool ret = false;
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testSignatureTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "setSelector", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSignatureTest");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getSelector", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(signatureComponent->getServiceByName("getSelector")->invoke()->getOwner())->getValue(), "testSignatureTest");
    
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamsCount", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_int)(signatureComponent->getServiceByName("getParamsCount")->invoke()->getOwner())->getValue(), 2);
    
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param1");
    
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(1)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param2");
    
    ret = false;
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(0)->getDefaultPort());
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("param3")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "setParamName", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    signatureComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(signatureComponent, "default", "getParamName", ret, retPort);
    BOOST_CHECK_EQUAL(signatureComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "param3");
    
    BOOST_CHECK_THROW(signatureComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(signatureComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(serviceInvocationComponentTest) {
    std::vector<ptr(ast_node)> paramsInner;
    paramsInner.push_back(new_ptr(ast_symbol)("paramInner"));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignatureInner"), paramsInner);
    
    ptr(ast_serviceinvocation) invocationAstInner = new_ptr(ast_serviceinvocation)(new_ptr(ast_symbol)("testReceiverInner"), new_ptr(ast_symbol)("testSelectorInner"), signAst);
    
    std::vector<ptr(ast_node)> paramsOuter;
    paramsOuter.push_back(new_ptr(ast_symbol)("param1"));
    paramsOuter.push_back(new_ptr(ast_string)("param2"));
    paramsOuter.push_back(new_ptr(ast_constant)(25));
    paramsOuter.push_back(invocationAstInner);
    
    signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignatureOuter"), paramsOuter);
    
    ptr(ast_serviceinvocation) invocationAst = new_ptr(ast_serviceinvocation)(new_ptr(ast_symbol)("testReceiver"), new_ptr(ast_symbol)("testSelector"), signAst);
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) invocationComponent = bootstrap1->bootstrapServiceInvocationComponent(invocationAst, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(invocationComponent->getParent(), 12, owner, bootstrap1);
    
    TEST_PRIMITIVE_PORT(invocationComponent, "receiver", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue(), "testReceiver");
    TEST_PRIMITIVE_PORT(invocationComponent, "selector", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSelector");
    TEST_PRIMITIVE_PORT(invocationComponent, "params", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("params")->getConnectedPortAt(0)->getOwner())->getValue(), "param1");
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("params")->getConnectedPortAt(1)->getOwner())->getValue(), "param2");
    BOOST_CHECK_EQUAL(cast(mem_int)(invocationComponent->getPortByName("params")->getConnectedPortAt(2)->getOwner())->getValue(), 25);
    
    ptr(mem_component) innerInv = invocationComponent->getPortByName("params")->getConnectedPortAt(3)->getOwner()->getChild();
    
    TEST_PRIMITIVE_PORT(innerInv, "receiver", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(innerInv->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue(), "testReceiverInner");
    TEST_PRIMITIVE_PORT(innerInv, "selector", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(innerInv->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSelectorInner");
    TEST_PRIMITIVE_PORT(innerInv, "params", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(innerInv->getPortByName("params")->getConnectedPortAt(0)->getOwner())->getValue(), "paramInner");
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    invocationComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testReceiverTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "setReceiver", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue(), "testReceiverTest");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "getReceiver", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testReceiverTest");
    
    ret = false;
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    invocationComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testSelectorTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "setSelector", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSelectorTest");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "getSelector", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testSelectorTest");
    
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "getParamsCount", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_int)(retPort->getOwner())->getValue(), 4);
    
    ret = false;
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    invocationComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testParam")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "addParam", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(invocationComponent->getPortByName("params")->getConnectedPortAt(4)->getOwner())->getValue(), "testParam");
    
    ret = true;
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    invocationComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(4)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(invocationComponent, "default", "getParamAt", ret, retPort);
    BOOST_CHECK_EQUAL(invocationComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testParam");
    
    BOOST_CHECK_THROW(invocationComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(invocationComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(namedInterfaceComponentTest) {
    
    ptr(ast_symbol) portName = new_ptr(ast_symbol)("testPort");
    bool atomicity = false;
    bool collectivity = false;
    type_visibility visibility = type_visibility::EXTERNAL;
    type_role role = type_role::PROVIDES;
    ptr(ast_symbol) componentName = new_ptr(ast_symbol)("testComponent");
    
    ptr(ast_namedport) astPort = new_ptr(ast_namedport)(portName, atomicity, collectivity, visibility, role, componentName);
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) interfaceComponent = bootstrap1->bootstrapInterfaceComponent(astPort, owner, nullptr);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT_PRIMITIVE(interfaceComponent->getParent(), 16, owner, bootstrap1);
    
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
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), PORT_TYPE_NAMED);
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), "testType");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testType");
    
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignaturesCount", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_int)(retPort->getOwner())->getValue(), 0);
    
    BOOST_CHECK_THROW(interfaceComponent->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getConnectedComponentName")->getPrimitiveService()->invoke(),
            exceptions::runtime::CWrongPortTypeException);
    
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
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) interfaceComponent = bootstrap1->bootstrapInterfaceComponent(astPort, owner, nullptr);
    
    ptr(mem_port) retPort;
    
    TEST_BASE_COMPONENT_PRIMITIVE(interfaceComponent->getParent(), 16, owner, bootstrap1);
    
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
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), PORT_TYPE_SIGNATURES);
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), "testType");
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testType");
    
    ret = false;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue(PORT_TYPE_SIGNATURES)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "setType", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(interfaceComponent->getPortByName("type")->getConnectedPortAt(0)->getOwner())->getValue(), PORT_TYPE_SIGNATURES);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignaturesCount", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_int)(retPort->getOwner())->getValue(), 3);
    
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(2)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner());
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
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapServiceSignatureComponent(signature, interfaceComponent)->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "addSignature", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    interfaceComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(3)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(interfaceComponent, "default", "getSignatureAt", ret, retPort);
    BOOST_CHECK_EQUAL(interfaceComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner());
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
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) portComponent = bootstrap1->bootstrapPortComponent(astPort, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(portComponent->getParent(), 13, owner, bootstrap1);
    
    TEST_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
    TEST_PRIMITIVE_PORT(portComponent, "isCollection", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(portComponent->getPortByName("isCollection")->getConnectedPortAt(0)->getOwner())->getValue(), false);
    
    ptr(mem_port) retPort;
    bool ret = true;
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "getName", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testPort");
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "getInterface", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner()->getPortByName("type")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), PORT_TYPE_NAMED);
    str = cast(mem_string)(retPort->getOwner()->getPortByName("componentName")->getConnectedPortAt(0)->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "testComponent");
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isConnected", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), false);
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isDelegated", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), false);
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isCollectionPort", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), false);
    
    ptr(mem_component) connectedComponent = bootstrap1->bootstrapComponent(nullptr);
    
    ret = false;
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    connectedComponent = bootstrap1->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", ret, retPort);
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
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) portComponent = bootstrap1->bootstrapCollectionPortComponent(astPort, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(portComponent->getParent(), 13, owner, bootstrap1);
    
    TEST_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
    TEST_PRIMITIVE_PORT(portComponent, "isCollection", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(portComponent->getPortByName("isCollection")->getConnectedPortAt(0)->getOwner())->getValue(), true);
    
    ptr(mem_component) connectedComponent = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(0)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    connectedComponent = bootstrap1->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(1)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    
    connectedComponent = bootstrap1->bootstrapComponent(nullptr);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    portComponent->getPortByName("args")->connectPort(connectedComponent->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "connectTo", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortAt(2)->getOwner().get(), connectedComponent.get());
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 3);
    
    portComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(2)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 2);
    
    portComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(1)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 1);
    
    portComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapIntValue(0)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "disconnectPort", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("connectedPorts")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portComponent, "default", "isCollectionPort", ret, retPort);
    BOOST_CHECK_EQUAL(portComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), true);
    
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
    
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) portDescriptionComponent = bootstrap1->bootstrapPortDescriptionComponent(astPort, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(portDescriptionComponent->getParent(), 17, owner, bootstrap1);
    
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
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("testPortDescriptionTest")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setName", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getName", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "testPortDescriptionTest");
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "testPortDescriptionTest");
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue(ROLE_REQUIREMENT)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setRole", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getRole", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), ROLE_REQUIREMENT);
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), ROLE_REQUIREMENT);
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("SelfPort")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setKind", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getKind", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "SelfPort");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "SelfPort");
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue(VISIBILITY_INTERNAL)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setVisibility", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getVisibility", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), VISIBILITY_INTERNAL);
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), VISIBILITY_INTERNAL);
    
    ret = false;
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapBoolValue(true)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setIsCollection", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "isCollection", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_bool)(retPort->getOwner())->getValue(), true);
    ptr(mem_bool) boolVal = cast(mem_bool)(retPort->getOwner());
    BOOST_CHECK_EQUAL(boolVal->getValue(), true);
    
    ret = false;
    ptr(mem_component) intf = bootstrap1->bootstrapInterfaceComponent(astPort, owner, nullptr);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    portDescriptionComponent->getPortByName("args")->connectPort(intf->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "setInterface", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(portDescriptionComponent, "default", "getInterface", ret, retPort);
    BOOST_CHECK_EQUAL(portDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(retPort->getOwner().get(), intf->getParent().get());
    
    BOOST_CHECK_THROW(portDescriptionComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(portDescriptionComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(namedConnectionDescriptionComponentTest) {
    ptr(ast_portaddress) addr1 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("default"), new_ptr(ast_symbol)("backend"));
    ptr(ast_portaddress) addr2 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("self"), new_ptr(ast_symbol)("frontend"));
    
    ptr(ast_connection) astConnection = new_ptr(ast_connection)(addr1, addr2);
        
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) connectionDescriptionComponent = bootstrap1->bootstrapConnectionDescriptionComponent(astConnection, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(connectionDescriptionComponent->getParent(), 27, owner, bootstrap1);
    
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponentIndex", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponentInvocation", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourceComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "backend");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourcePort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourcePort")->getConnectedPortAt(0)->getOwner())->getValue(), "default");
    
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponentIndex", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponentInvocation", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "frontend");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationPort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationPort")->getConnectedPortAt(0)->getOwner())->getValue(), "self");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "bindType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("bindType")->getConnectedPortAt(0)->getOwner())->getValue(), BIND_CONNECTION);
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newBackend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourceComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourceComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newBackend");
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newBackend");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newDefault")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourcePort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourcePort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newDefault");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newDefault");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newFrontend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newFrontend");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newFrontend");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newSelf")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationPort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationPort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newSelf");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newSelf");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue(BIND_DISCONNECTION)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setBindType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getBindType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), BIND_DISCONNECTION);
    ptr(mem_string) stringVal = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(stringVal->getValue(), BIND_DISCONNECTION);
    
    BOOST_CHECK_THROW(connectionDescriptionComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(connectionDescriptionComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_CASE(signatureConnectionDescriptionComponentTest) {
    std::vector<ptr(ast_node)> paramsOuter;
    paramsOuter.push_back(new_ptr(ast_symbol)("param1"));
    paramsOuter.push_back(new_ptr(ast_string)("param2"));
    paramsOuter.push_back(new_ptr(ast_constant)(25));
    
    ptr(ast_servicesignature) signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("testSignatureOuter"), paramsOuter);
    
    ptr(ast_serviceinvocation) invocationAst = new_ptr(ast_serviceinvocation)(new_ptr(ast_symbol)("testReceiver"), new_ptr(ast_symbol)("testSelector"), signAst);
    
    ptr(ast_portaddress) addr1 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("default"), invocationAst);
    ptr(ast_portaddress) addr2 = new_ptr(ast_portaddress)(new_ptr(ast_symbol)("self"), new_ptr(ast_symbol)("frontend"));
    
    ptr(ast_connection) astConnection = new_ptr(ast_connection)(addr1, addr2);
        
    ptr(mem_component) owner = bootstrap1->bootstrapComponent(nullptr);
    
    ptr(mem_component) connectionDescriptionComponent = bootstrap1->bootstrapConnectionDescriptionComponent(astConnection, owner);
    
    TEST_BASE_COMPONENT_PRIMITIVE(connectionDescriptionComponent->getParent(), 27, owner, bootstrap1);
    
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourceType")->getConnectedPortAt(0)->getOwner())->getValue(), CONNECTION_INVOCATION);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponentIndex", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponentInvocation", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)
            (connectionDescriptionComponent
            ->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()
            ->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue(), "testReceiver");
    BOOST_CHECK_EQUAL(cast(mem_string)
            (connectionDescriptionComponent
            ->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()
            ->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "testSelector");
    BOOST_CHECK_EQUAL(cast(mem_string)
            (connectionDescriptionComponent
            ->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()
            ->getPortByName("params")->getConnectedPortAt(0)->getOwner())->getValue(), "param1");
    BOOST_CHECK_EQUAL(cast(mem_string)
            (connectionDescriptionComponent
            ->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()
            ->getPortByName("params")->getConnectedPortAt(1)->getOwner())->getValue(), "param2");
    BOOST_CHECK_EQUAL(cast(mem_int)
            (connectionDescriptionComponent
            ->getPortByName("sourceComponentInvocation")->getConnectedPortAt(0)->getOwner()
            ->getPortByName("params")->getConnectedPortAt(2)->getOwner())->getValue(), 25);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourceComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "sourcePort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("sourcePort")->getConnectedPortAt(0)->getOwner())->getValue(), "default");
    
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationType")->getConnectedPortAt(0)->getOwner())->getValue(), CONNECTION_NAMED);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponentIndex", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponentInvocation", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationComponent", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationComponent")->getConnectedPortAt(0)->getOwner())->getValue(), "frontend");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "destinationPort", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("destinationPort")->getConnectedPortAt(0)->getOwner())->getValue(), "self");
    TEST_PRIMITIVE_PORT(connectionDescriptionComponent, "bindType", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(connectionDescriptionComponent->getPortByName("bindType")->getConnectedPortAt(0)->getOwner())->getValue(), BIND_CONNECTION);
    
    ptr(mem_port) retPort;
    bool ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newBackend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourceComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourceComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newBackend");
    ptr(mem_string) str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newBackend");
    
    paramsOuter.clear();
    paramsOuter.push_back(new_ptr(ast_symbol)("new_param1"));
    paramsOuter.push_back(new_ptr(ast_string)("new_param2"));
    paramsOuter.push_back(new_ptr(ast_constant)(358));
    
    signAst = new_ptr(ast_servicesignature)(new_ptr(ast_symbol)("new_testSignatureOuter"), paramsOuter);
    
    invocationAst = new_ptr(ast_serviceinvocation)(new_ptr(ast_symbol)("new_testReceiver"), new_ptr(ast_symbol)("new_testSelector"), signAst);
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapServiceInvocationComponent(invocationAst, nullptr)->getPortByName("default"));
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourceComponentInvocation", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourceComponentInvocation", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner()->getPortByName("receiver")->getConnectedPortAt(0)->getOwner())->getValue(), "new_testReceiver");
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner()->getPortByName("selector")->getConnectedPortAt(0)->getOwner())->getValue(), "new_testSelector");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourceType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourceType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newType");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newType");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newDefault")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setSourcePort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getSourcePort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newDefault");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newDefault");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newFrontend")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationComponent", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newFrontend");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newFrontend");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newType")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newType");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newType");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue("newSelf")->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setDestinationPort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getDestinationPort", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), "newSelf");
    str = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(str->getValue(), "newSelf");
    
    ret = false;
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    connectionDescriptionComponent->getPortByName("args")->connectPort(bootstrap1->bootstrapStringValue(BIND_DISCONNECTION)->getDefaultPort());
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "setBindType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    
    ret = true;
    TEST_PRIMITIVE_SERVICE(connectionDescriptionComponent, "default", "getBindType", ret, retPort);
    BOOST_CHECK_EQUAL(connectionDescriptionComponent->getPortByName("args")->getConnectedPortsNumber(), 0);
    BOOST_CHECK_EQUAL(cast(mem_string)(retPort->getOwner())->getValue(), BIND_DISCONNECTION);
    ptr(mem_string) stringVal = cast(mem_string)(retPort->getOwner());
    BOOST_CHECK_EQUAL(stringVal->getValue(), BIND_DISCONNECTION);
    
    BOOST_CHECK_THROW(connectionDescriptionComponent->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(connectionDescriptionComponent->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_SUITE_END()
