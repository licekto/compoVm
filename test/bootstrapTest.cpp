#include <iostream>
#include <memory>
#include <typeinfo>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"
#include "types.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "interpreter/memory/objects/values/stringComponent.h"

BOOST_AUTO_TEST_SUITE(bootstrapTest)

BOOST_AUTO_TEST_CASE(basicTest) {
    // Crete parser, core modules, interpreter and bootstrap
    ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());
    ptr(interpreter::core::CCoreModules) coreModules = new_ptr(interpreter::core::CCoreModules)(parser);
    ptr(interpreter::core::CInterpreter) interpreter = new_ptr(interpreter::core::CInterpreter)(parser, coreModules);
    ptr(interpreter::core::CBootstrap) bootstrap = new_ptr(interpreter::core::CBootstrap)(coreModules, interpreter);
    
    // Bootstrap
    bootstrap->boostrap();
    
    ptr(interpreter::memory::objects::CComponent) component = bootstrap->getCoreComponent(interpreter::core::coreModuleType::COMPONENT);
    
    BOOST_CHECK(component->getPortByName("default")->isPrimitive());
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getName(), "default");
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getOwner().get(), component.get());
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getRole(), types::roleType::PROVIDES);
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getVisibility(), types::visibilityType::EXTERNAL);
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getPrimitivePort()->getName(), "default");
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getPrimitivePort()->getOwner().get(), component.get());
    BOOST_CHECK_EQUAL(component->getPortByName("default")->getPrimitivePort()->getConnectedServicesNumber(), 5);
    BOOST_CHECK(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceAt(0)->isPrimitive());
    BOOST_CHECK(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceAt(1)->isPrimitive());
    BOOST_CHECK(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceAt(2)->isPrimitive());
    BOOST_CHECK(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceAt(3)->isPrimitive());
    BOOST_CHECK(component->getPortByName("default")->getPrimitivePort()->getConnectedServiceAt(4)->isPrimitive());
    
    ptr(interpreter::memory::objects::CGeneralService) generalService;
    ptr(interpreter::memory::objects::CComponent) retVal;
    
    generalService = component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getPorts");
    BOOST_CHECK(generalService->isPrimitive());
    BOOST_CHECK_EQUAL(generalService->getName(), "getPorts");
    BOOST_CHECK_EQUAL(generalService->getPrimitiveService()->getArgumentsNamesCount(), 0);
    retVal = generalService->getPrimitiveService()->invoke();
    BOOST_CHECK_EQUAL(retVal.use_count(), 0);
    
    generalService = component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getPortNamed");
    BOOST_CHECK(generalService->isPrimitive());
    BOOST_CHECK_EQUAL(generalService->getName(), "getPortNamed");
    BOOST_CHECK_EQUAL(generalService->getPrimitiveService()->getArgumentsNamesCount(), 1);
    
    ptr(interpreter::memory::objects::values::CStringComponent) nameComponent = new_ptr(interpreter::memory::objects::values::CStringComponent)("default");
    ptr(interpreter::memory::objects::primitives::CPrimitivePort) primitivePort = new_ptr(interpreter::memory::objects::primitives::CPrimitivePort)("default", nameComponent);
    ptr(interpreter::memory::objects::CGeneralPort) generalPort = new_ptr(interpreter::memory::objects::CGeneralPort)(primitivePort, types::visibilityType::EXTERNAL, types::roleType::PROVIDES);
    nameComponent->addDefaultPort(generalPort);
    
    component->getPortByName("args")->getPrimitivePort()->connectPort(nameComponent->getDefaultPort());
    retVal = generalService->getPrimitiveService()->invoke();
    BOOST_CHECK_EQUAL(retVal.use_count(), 0);
    
    generalService = component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getDescriptor");
    BOOST_CHECK(generalService->isPrimitive());
    BOOST_CHECK_EQUAL(generalService->getName(), "getDescriptor");
    BOOST_CHECK_EQUAL(generalService->getPrimitiveService()->getArgumentsNamesCount(), 0);
    retVal = generalService->getPrimitiveService()->invoke();
    BOOST_CHECK_EQUAL(retVal.use_count(), 0);
    
    generalService = component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getOwner");
    BOOST_CHECK(generalService->isPrimitive());
    BOOST_CHECK_EQUAL(generalService->getName(), "getOwner");
    BOOST_CHECK_EQUAL(generalService->getPrimitiveService()->getArgumentsNamesCount(), 0);
    retVal = generalService->getPrimitiveService()->invoke();
    BOOST_CHECK_EQUAL(retVal.get(), component.get());
    
    generalService = component->getPortByName("default")->getPrimitivePort()->getConnectedServiceByName("getIdentityHash");
    BOOST_CHECK(generalService->isPrimitive());
    BOOST_CHECK_EQUAL(generalService->getName(), "getIdentityHash");
    BOOST_CHECK_EQUAL(generalService->getPrimitiveService()->getArgumentsNamesCount(), 0);
    retVal = generalService->getPrimitiveService()->invoke();
    BOOST_CHECK_EQUAL(retVal.use_count(), 0);
}

BOOST_AUTO_TEST_SUITE_END()
