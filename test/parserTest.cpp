#include <boost/test/unit_test.hpp>

#include <iostream>

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

BOOST_AUTO_TEST_CASE(compo_basic_structure) {    
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
    
    BOOST_CHECK_EQUAL(std::string("HTTPServer"), descriptor->getName()->getStringValue());
    BOOST_CHECK_EQUAL(std::string("server"), descriptor->getExtends()->getStringValue());
    
    const std::vector<compo::CCompoNode*> * bodyPtr = descriptor->getBody();
    
    BOOST_CHECK_EQUAL(bodyPtr->size(), 4);
    
    compo::CCompoProvision *provision = dynamic_cast<compo::CCompoProvision *>(bodyPtr->at(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PROVISION, provision->getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, provision->getVisibilityType());    
    std::vector<compo::CCompoPort*> * ports = provision->getPorts();
    BOOST_CHECK_EQUAL(1, ports->size());
    compo::CCompoPort *port = ports->at(0);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, port->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), port->getName()->getStringValue());
    
    
    compo::CCompoRequirement *requirement = dynamic_cast<compo::CCompoRequirement *>(bodyPtr->at(1));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::REQUIREMENT, requirement->getNodeType());
    BOOST_CHECK_EQUAL(compo::visibilityType::EXTERNAL, requirement->getVisibilityType());    
    ports = requirement->getPorts();
    BOOST_CHECK_EQUAL(1, ports->size());
    port = ports->at(0);
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::PORT, port->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), port->getName()->getStringValue());
    
    
    compo::CCompoService *service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(2));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("create"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(0, service->getParams()->size());
    
    
    compo::CCompoConstraint *constraint = dynamic_cast<compo::CCompoConstraint *>(bodyPtr->at(3));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::CONSTRAINT, constraint->getNodeType());
    BOOST_CHECK_EQUAL(std::string("httpOnly"), constraint->getName()->getStringValue());
    
    parser.clear();
}

BOOST_AUTO_TEST_CASE(compo_service) {    
    std::stringstream input;
    input.str("descriptor test {\
	service noparams() {}\
        service oneparam(param) {}\
        service twoparams(param1, param2) {}\
        service threeparams(param1, param2, param3) {}\
        service body() {a;}\
    }");

    parser.parse(input);    
    
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    compo::CCompoDescriptor *descriptor = (compo::CCompoDescriptor*) parser.getRootNodeAt(0);
    const std::vector<compo::CCompoNode*> * bodyPtr = descriptor->getBody();
    
    BOOST_CHECK_EQUAL(bodyPtr->size(), 5);
    
    compo::CCompoService *service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(0));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("noparams"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(0, service->getParams()->size());
    
    service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(1));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("oneparam"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(1, service->getParams()->size());
    
    service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(2));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("twoparams"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(2, service->getParams()->size());
    
    service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(3));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("threeparams"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(3, service->getParams()->size());
    
    service = dynamic_cast<compo::CCompoService *>(bodyPtr->at(4));
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("body"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(0, service->getParams()->size());
    BOOST_CHECK_EQUAL(1, service->getBody()->size());
    BOOST_CHECK_EQUAL(compo::NodeTypeEnum::SYMBOL, service->getBody()->at(0)->getNodeType());
    
    compo::CCompoSymbol *symbol = dynamic_cast<compo::CCompoSymbol*>(service->getBody()->at(0));
    BOOST_CHECK_EQUAL("a", symbol->getStringValue());
    
    parser.clear();
}

BOOST_AUTO_TEST_CASE(compo_for) {
    
}

BOOST_AUTO_TEST_SUITE_END()