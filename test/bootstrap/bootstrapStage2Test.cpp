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
ptr(core_bootstrap1) bootstrap1 = new_ptr(core_bootstrap1)(coreModules);
ptr(core_bootstrap2) bootstrap2 = new_ptr(core_bootstrap2)(bootstrap1);

BOOST_AUTO_TEST_CASE(componentStage2Test) {
    // Testing input
    std::stringstream input;
    input.str(
    "descriptor HTTPServer {\
	externally provides {\
		req : Handler;\
	}\
	service create() {}\
        architecture {\
            connect a@b to b@c;\
        }\
    }");
    // Parse input and create AST
    parser->parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptorAst = cast(ast_descriptor)(parser->getRootNode()->getNodeAt(0));
    
    std::cout << descriptorAst->getNameSymbol()->getStringValue() << std::endl;
    
    ptr(mem_component) descriptorComponent = bootstrap2->bootstrapDescriptorComponent(descriptorAst);
    
    TEST_DESCRIPTOR_COMPONENT(descriptorComponent, "HTTPServer", "",11, 19, 1, 1, 1);
}

BOOST_AUTO_TEST_SUITE_END()
