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

BOOST_AUTO_TEST_CASE(compo_basic_structure) {
    Lexer lexer;
    ParserWrapper parser(&lexer);
    
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
    
    /*
    while (1) {
        if (!parser.parse(input)) {
            break;
        }
    }
    */
        
    BOOST_CHECK_EQUAL(NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    CCompoDescriptor *descriptor = (CCompoDescriptor*) parser.getRootNodeAt(0);
    
    BOOST_CHECK_EQUAL(std::string("HTTPServer"), descriptor->getName()->getStringValue());
    BOOST_CHECK_EQUAL(std::string("server"), descriptor->getExtends()->getStringValue());
    
    const std::vector<CCompoNode*> * bodyPtr = descriptor->getBody();
    
    BOOST_CHECK_EQUAL(bodyPtr->size(), 4);
    
    CCompoProvision *provision = dynamic_cast<CCompoProvision *>(bodyPtr->at(0));
    BOOST_CHECK_EQUAL(NodeTypeEnum::PROVISION, provision->getNodeType());
    BOOST_CHECK_EQUAL(visibilityType::EXTERNAL, provision->getVisibilityType());    
    std::vector<CCompoPort*> * ports = provision->getPorts();
    BOOST_CHECK_EQUAL(1, ports->size());
    CCompoPort *port = ports->at(0);
    BOOST_CHECK_EQUAL(NodeTypeEnum::PORT, port->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), port->getName()->getStringValue());
    
    
    CCompoRequirement *requirement = dynamic_cast<CCompoRequirement *>(bodyPtr->at(1));
    BOOST_CHECK_EQUAL(NodeTypeEnum::REQUIREMENT, requirement->getNodeType());
    BOOST_CHECK_EQUAL(visibilityType::EXTERNAL, requirement->getVisibilityType());    
    ports = requirement->getPorts();
    BOOST_CHECK_EQUAL(1, ports->size());
    port = ports->at(0);
    BOOST_CHECK_EQUAL(NodeTypeEnum::PORT, port->getNodeType());
    BOOST_CHECK_EQUAL(std::string("default"), port->getName()->getStringValue());
    
    
    CCompoService *service = dynamic_cast<CCompoService *>(bodyPtr->at(2));
    BOOST_CHECK_EQUAL(NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("create"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(0, service->getParams()->size());
    
    
    CCompoConstraint *constraint = dynamic_cast<CCompoConstraint *>(bodyPtr->at(3));
    BOOST_CHECK_EQUAL(NodeTypeEnum::CONSTRAINT, constraint->getNodeType());
    BOOST_CHECK_EQUAL(std::string("httpOnly"), constraint->getName()->getStringValue());
}

BOOST_AUTO_TEST_CASE(compo_service) {
    Lexer lexer;
    ParserWrapper parser(&lexer);
    
    std::stringstream input;
    input.str("descriptor test {\
	service noparams() {}\
        service oneparam(param) {}\
        service twoparams(param1, param2) {}\
        service threeparams(param1, param2, param3) {}\
    }");

    parser.parse(input);    
    
    BOOST_CHECK_EQUAL(NodeTypeEnum::DESCRIPTOR, parser.getRootNodeAt(0)->getNodeType());
    
    CCompoDescriptor *descriptor = (CCompoDescriptor*) parser.getRootNodeAt(0);
    const std::vector<CCompoNode*> * bodyPtr = descriptor->getBody();
    
    BOOST_CHECK_EQUAL(bodyPtr->size(), 4);
    
    CCompoService *service = dynamic_cast<CCompoService *>(bodyPtr->at(0));
    BOOST_CHECK_EQUAL(NodeTypeEnum::SERVICE, service->getNodeType());
    BOOST_CHECK_EQUAL(std::string("noparams"), service->getName()->getStringValue());
    BOOST_CHECK_EQUAL(0, service->getParams()->size());
}

BOOST_AUTO_TEST_SUITE_END()