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

BOOST_AUTO_TEST_SUITE(bootstrapTest)

// Create parser, core modules, interpreter and bootstrap
ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
ptr(core_modules) coreModules = new_ptr(core_modules)(parser);
ptr(core_bootstrap1) bootstrap = new_ptr(core_bootstrap1)(coreModules/*, interpreter*/);

BOOST_AUTO_TEST_CASE(componentStage2Test) {
    // Bootstrap
    
    ptr(mem_component) owner;
    
    ptr(mem_component) component = bootstrap->bootstrapComponent(owner);
    
    TEST_COMPONENT(component, owner);
    
    BOOST_CHECK_THROW(component->getServiceByName("abcd"), exceptions::runtime::CServiceNotFoundException);
    BOOST_CHECK_THROW(component->getPortByName("abcd"), exceptions::runtime::CPortNotFoundException);
}

BOOST_AUTO_TEST_SUITE_END()
