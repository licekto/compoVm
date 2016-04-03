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
    
    // Get Descriptor component
//    ptr(interpreter::memory::objects::CComponent) descriptor = bootstrap->getCoreComponent(interpreter::core::coreModuleType::DESCRIPTOR);
    
    // Check Descriptor component
    /*
    BOOST_CHECK_EQUAL(descriptor->getNumberOfPorts(), 4);
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_port->getPrimitivePortByName("name")->getName(), "name");
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_type, interpreter::memory::objects::portType::REQUIREMENT);
    BOOST_CHECK_EQUAL(descriptor->getPortAt(0)->m_visibility, interpreter::memory::objects::portVisibility::INTERNAL);
    ptr(interpreter::memory::objects::primitives::CPrimitivePort) primitivePort = cast(interpreter::memory::objects::primitives::CPrimitivePort)
            (descriptor->getPortAt(0)->m_port->getPrimitivePortByName("name"));
     * */
    
//    ptr(interpreter::memory::objects::CComponent) component = bootstrap->getCoreComponent(interpreter::core::coreModuleType::COMPONENT);
//    
//    BOOST_CHECK_EQUAL(component->getNumberOfPorts(), 4);
//    
//    ptr(interpreter::memory::objects::primitives::CPrimitivePortProperties) primitivePortProperties = 
//            cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("args"));
//    BOOST_CHECK_EQUAL(primitivePortProperties->getType(), interpreter::memory::objects::portType::REQUIREMENT);
//    BOOST_CHECK_EQUAL(primitivePortProperties->getVisibility(), interpreter::memory::objects::portVisibility::EXTERNAL);
//    ptr(interpreter::memory::objects::primitives::CPrimitiveCollectionPort) primitiveCollectionPort = cast(interpreter::memory::objects::primitives::CPrimitiveCollectionPort)(primitivePortProperties->getPrimitivePort());
//    BOOST_CHECK_EQUAL(primitiveCollectionPort->getName(), "args");
//    BOOST_CHECK_EQUAL(primitiveCollectionPort->getOwner().get(), component.get());
//    
//    primitivePortProperties = cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("default"));
//    BOOST_CHECK_EQUAL(primitivePortProperties->getType(), interpreter::memory::objects::portType::PROVISION);
//    BOOST_CHECK_EQUAL(primitivePortProperties->getVisibility(), interpreter::memory::objects::portVisibility::EXTERNAL);
//    ptr(interpreter::memory::objects::primitives::CPrimitivePort) primitivePort = cast(interpreter::memory::objects::primitives::CPrimitivePort)(primitivePortProperties->getPrimitivePort());
//    BOOST_CHECK_EQUAL(primitivePort->getName(), "default");
//    BOOST_CHECK_EQUAL(primitivePort->getOwner().get(), component.get());
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServicesNumber(),5);
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(0)->getPrimitiveService()->getName(), "getDescriptor");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(1)->getPrimitiveService()->getName(), "getIdentityHash");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(2)->getPrimitiveService()->getName(), "getOwner");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(3)->getPrimitiveService()->getName(), "getPortNamed");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(4)->getPrimitiveService()->getName(), "getPorts");
//    
//    
//    primitivePortProperties = cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("super"));
//    BOOST_CHECK_EQUAL(primitivePortProperties->getType(), interpreter::memory::objects::portType::PROVISION);
//    BOOST_CHECK_EQUAL(primitivePortProperties->getVisibility(), interpreter::memory::objects::portVisibility::INTERNAL);
//    primitivePort = cast(interpreter::memory::objects::primitives::CPrimitivePort)(primitivePortProperties->getPrimitivePort());
//    BOOST_CHECK_EQUAL(primitivePort->getName(), "super");
//    BOOST_CHECK_EQUAL(primitivePort->getOwner().get(), component.get());
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServicesNumber(),0);
//    
//    primitivePortProperties = cast(interpreter::memory::objects::primitives::CPrimitivePortProperties)(component->getPortByName("self"));
//    BOOST_CHECK_EQUAL(primitivePortProperties->getType(), interpreter::memory::objects::portType::PROVISION);
//    BOOST_CHECK_EQUAL(primitivePortProperties->getVisibility(), interpreter::memory::objects::portVisibility::INTERNAL);
//    primitivePort = cast(interpreter::memory::objects::primitives::CPrimitivePort)(primitivePortProperties->getPrimitivePort());
//    BOOST_CHECK_EQUAL(primitivePort->getName(), "self");
//    BOOST_CHECK_EQUAL(primitivePort->getOwner().get(), component.get());
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServicesNumber(),5);
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(0)->getPrimitiveService()->getName(), "getDescriptor");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(1)->getPrimitiveService()->getName(), "getIdentityHash");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(2)->getPrimitiveService()->getName(), "getOwner");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(3)->getPrimitiveService()->getName(), "getPortNamed");
//    BOOST_CHECK_EQUAL(primitivePort->getConnectedServiceAt(4)->getPrimitiveService()->getName(), "getPorts");
}

BOOST_AUTO_TEST_SUITE_END()
