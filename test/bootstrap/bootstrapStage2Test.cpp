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

BOOST_AUTO_TEST_SUITE(bootstrapStage2Test)

ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());

ptr(core_bootstrap2) init() {
    // Create parser, core modules, interpreter and bootstrap
    ptr(core_modules) coreModules = new_ptr(core_modules)(parser);
    ptr(interpreter::memory::memspace::CMemory) memory = new_ptr(interpreter::memory::memspace::CMemory)();
    ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(coreModules, nullptr, memory);
    memory->setBootstrap1(bootstrap1);
    ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);
    
    return bootstrap2;
}

ptr(core_bootstrap2) bootstrap2 = init();

BOOST_AUTO_TEST_CASE(basicTest) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor HTTPServer {\
	externally provides {\
		req : Handler;\
	}\
        internally provides {\
		fE : FrontEnd;\
                bE : BackEnd;\
	}\
	service create() {}\
    }");
    // Parse input and create AST
    parser->parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptorAst = cast(ast_descriptor)(parser->getRootNode()->getNodeAt(0));
    
    ptr(mem_component) descriptorComponent = bootstrap2->bootstrapDescriptorComponent(descriptorAst);
    
    TEST_BASE_COMPONENT_COMPONENT(descriptorComponent);
    
    TEST_DESCRIPTOR_COMPONENT(descriptorComponent, "HTTPServer", "", 3, 1, 0);
    
    ptr(mem_port) port = descriptorComponent->getServiceByName("new")->invoke();
    
    ptr(mem_component) newComponent = port->getOwner();
    
    TEST_BASE_COMPONENT_COMPONENT(newComponent);
    TEST_PORT_COMPONENT(newComponent->getPortByName("req")->getPort(), "req", 0);
    TEST_PORT_COMPONENT(newComponent->getPortByName("fE")->getPort(), "fE", 0);
    TEST_PORT_COMPONENT(newComponent->getPortByName("bE")->getPort(), "bE", 0);
}

BOOST_AUTO_TEST_SUITE_END()
