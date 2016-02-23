#include <iostream>

#include <boost/test/unit_test.hpp>

#include "lexer.h"
#include "parserWrapper.h"
#include "compoDescriptor.h"
#include "compoProvision.h"
#include "compoRequirement.h"
#include "compoService.h"
#include "compoConstraint.h"


BOOST_AUTO_TEST_SUITE(parser)

Lexer lexer;
ParserWrapper parser(&lexer);

BOOST_AUTO_TEST_CASE(compoBasicStructure) {    
    std::stringstream input;
    input.str("descriptor HTTPServer extends server {\
	externally provides {\
		default : {};\
	}\
        externally requires {\
            default : {};\
        }\
	service create() {}\
        constraint httpOnly() {}\
    }");
    
    parser.parse(input);
        
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    compo::CCompoDescriptor *descriptor = (compo::CCompoDescriptor*) parser.getRootNodeAt(0);
    
    BOOST_CHECK_EQUAL(std::string("HTTPServer"), descriptor->getName());
    BOOST_CHECK_EQUAL(std::string("server"), descriptor->getExtends());
    
    BOOST_CHECK_EQUAL(4, descriptor->getBodySize());
    
    compo::CCompoProvision *provision = dynamic_cast<compo::CCompoProvision *>(descriptor->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision->getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision->getVisibilityType());    
    BOOST_CHECK_EQUAL(1, provision->getNumberOfPorts());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, provision->getPortAt(0)->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), provision->getPortAt(0)->getName());
    
    
    compo::CCompoRequirement *requirement = dynamic_cast<compo::CCompoRequirement *>(descriptor->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement->getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement->getVisibilityType());
    BOOST_CHECK_EQUAL(1, requirement->getNumberOfPorts());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, requirement->getPortAt(0)->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), requirement->getPortAt(0)->getName());
    
    
    compo::CCompoService *service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("create"), service->getName());
    BOOST_CHECK_EQUAL(0, service->getParamsSize());
    
    
    compo::CCompoConstraint *constraint = dynamic_cast<compo::CCompoConstraint *>(descriptor->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint->getNodeType());
    BOOST_CHECK_EQUAL(std::string("httpOnly"), constraint->getName());
    
    parser.clear();
}

BOOST_AUTO_TEST_CASE(compoServiceParams) {
    std::stringstream input;
    input.str("descriptor test {\
	service noparams() {}\
        service oneparam(param) {}\
        service twoparams(param1, param2) {}\
        service threeparams(param1, param2, param3) {}\
    }");

    parser.parse(input);    
    
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    compo::CCompoDescriptor *descriptor = (compo::CCompoDescriptor*) parser.getRootNodeAt(0);
    
    BOOST_CHECK_EQUAL(4, descriptor->getBodySize());
    
    compo::CCompoService *service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("noparams"), service->getName());
    BOOST_CHECK_EQUAL(0, service->getParamsSize());
    
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("oneparam"), service->getName());
    BOOST_CHECK_EQUAL(1, service->getParamsSize());
    
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("twoparams"), service->getName());
    BOOST_CHECK_EQUAL(2, service->getParamsSize());
    
    service = dynamic_cast<compo::CCompoService *>(descriptor->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("threeparams"), service->getName());
    BOOST_CHECK_EQUAL(3, service->getParamsSize());
    
    parser.clear();
}

BOOST_AUTO_TEST_CASE(compoServiceBody) {
    std::stringstream input;
    input.str("descriptor test {\
        service body1() {a;}\
        service body2() {a := 1;}\
    }");
    
    parser.parse(input);    
    
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    compo::CCompoDescriptor *descriptor = (compo::CCompoDescriptor*) parser.getRootNodeAt(0);
    
    BOOST_CHECK_EQUAL(2, descriptor->getBodySize());
    
    compo::CCompoService *service = dynamic_cast<compo::CCompoService*>(descriptor->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("body1"), service->getName());
    BOOST_CHECK_EQUAL(0, service->getParamsSize());
    BOOST_CHECK_EQUAL(1, service->getBodySize());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, service->getBodyNodeAt(0)->getNodeType());
    
    compo::CCompoSymbol *symbol = dynamic_cast<compo::CCompoSymbol*>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL("a", symbol->getStringValue());
}

BOOST_AUTO_TEST_SUITE_END()