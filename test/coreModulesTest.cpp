#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "interpreter/core/interpreter.h"
#include "interpreter/core/coreModules.h"
#include "interpreter/core/bootstrap.h"

BOOST_AUTO_TEST_SUITE(coreModulesTest)

BOOST_AUTO_TEST_CASE(basicTest) {
    
    ptr(ParserWrapper) parser = new_ptr(ParserWrapper)(new_ptr(Lexer)(), new_ptr(ast::semantic::CSyntaxDescriptorTable)());
    
    ptr(interpreter::core::CCoreModules) coreModules = new_ptr(interpreter::core::CCoreModules)(parser);
    
    coreModules->loadCoreModules();
    
    BOOST_CHECK_EQUAL(coreModules->getCoreDescriptorsSize(), 9);
    
    ptr(ast_descriptor) descriptor = coreModules->getCoreDescriptor("CollectionPort");
    TEST_DESCRIPTOR(descriptor, "CollectionPort", "Port", 0, 2, 0);
    
    descriptor = coreModules->getCoreDescriptor("Component");
    TEST_DESCRIPTOR(descriptor, "Component", "", 5, 5, 0);
    
    descriptor = coreModules->getCoreDescriptor("ConnectionDescription");
    TEST_DESCRIPTOR(descriptor, "ConnectionDescription", "Component", 5, 10, 0);
    
    descriptor = coreModules->getCoreDescriptor("Descriptor");
    TEST_DESCRIPTOR(descriptor, "Descriptor", "Component", 4, 11, 0);
    
    descriptor = coreModules->getCoreDescriptor("Interface");
    TEST_DESCRIPTOR(descriptor, "Interface", "Component", 5, 11, 0);
    
    descriptor = coreModules->getCoreDescriptor("Port");
    TEST_DESCRIPTOR(descriptor, "Port", "Component", 5, 7, 0);
    
    descriptor = coreModules->getCoreDescriptor("PortDescription");
    TEST_DESCRIPTOR(descriptor, "PortDescription", "Component", 6, 12, 0);
    
    descriptor = coreModules->getCoreDescriptor("Service");
    TEST_DESCRIPTOR(descriptor, "Service", "Component", 4, 1, 0);
    
    descriptor = coreModules->getCoreDescriptor("ServiceSignature");
    TEST_DESCRIPTOR(descriptor, "ServiceSignature", "Component", 2, 5, 0);
}

BOOST_AUTO_TEST_SUITE_END()
