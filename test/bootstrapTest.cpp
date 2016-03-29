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
    
    ptr(interpreter::core::CBootstrap) bootstrap =
            new_ptr(interpreter::core::CBootstrap)                              // new Boostrap
               (new_ptr(interpreter::core::CCoreModules)                        // new Core Modules
                   (new_ptr(ParserWrapper)                                      // new Parser
                       (new_ptr(Lexer)(),                                       // new Lexer
                        new_ptr(ast::semantic::CGlobalDescriptorTable)())),     // new Descriptor table
                new_ptr(interpreter::core::CInterpreter)(parser, coreModules)); // new Interpreter
    
    // run bootstrapping
    bootstrap->boostrap();
    
    // get Descriptor component
    ptr(interpreter::memory::objects::CComponent) descriptor = bootstrap->getCoreComponent(interpreter::core::coreModuleType::DESCRIPTOR);
    
    // check Descriptor component
    BOOST_CHECK_EQUAL(descriptor->getNumberOfPorts(), 4);
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_port->getPrimitivePortByName("name")->getName(), "name");
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_type, interpreter::memory::objects::portType::REQUIREMENT);
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_visibility, interpreter::memory::objects::portVisibility::INTERNAL);
    ptr(interpreter::memory::objects::primitives::CPrimitivePort) primitivePort = cast(interpreter::memory::objects::primitives::CPrimitivePort)
            (descriptor->getPortAt(0)->m_port->getPrimitivePortByName("name"));
    
}

BOOST_AUTO_TEST_SUITE_END()
