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
    
    //TEST_GENERAL_PRIMITIVE_PORT(portComponent, "name", types::roleType::REQUIRES, types::visibilityType::INTERNAL, 0);
    //BOOST_CHECK_EQUAL(cast(mem_string)(portComponent->getPortByName("name")->getConnectedPortAt(0)->getOwner())->getValue(), "testPort");
}

BOOST_AUTO_TEST_SUITE_END()
