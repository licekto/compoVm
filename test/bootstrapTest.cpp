#include <iostream>
#include <memory>
#include <typeinfo>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"
#include "interpreter/memory/objects/primitives/primitivePort.h"
#include "generated/parser.h"

BOOST_AUTO_TEST_SUITE(bootstrapTest)

BOOST_AUTO_TEST_CASE(basicTest) {
    // Crete parser, core modules, interpreter and bootstrap
    ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CGlobalDescriptorTable)());
    ptr(interpreter::core::CCoreModules) coreModules = new_ptr(interpreter::core::CCoreModules)(parser);
    ptr(interpreter::core::CInterpreter) interpreter = new_ptr(interpreter::core::CInterpreter)(parser, coreModules);
    ptr(interpreter::core::CBootstrap) bootstrap = new_ptr(interpreter::core::CBootstrap)(coreModules, interpreter);
    
    // Bootstrap
    bootstrap->boostrap();
}

BOOST_AUTO_TEST_SUITE_END()
