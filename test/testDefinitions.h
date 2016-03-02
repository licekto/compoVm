#pragma once

#include <iostream>
#include <vector>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"
#include "nodes/compo/descriptor.h"
#include "nodes/compo/service.h"
#include "nodes/procedural/assignmentExpression.h"
#include "nodes/procedural/constant.h"
#include "nodes/procedural/stringLiteral.h"
#include "nodes/procedural/parens.h"
#include "nodes/procedural/additionExpression.h"
#include "nodes/procedural/subtractionExpression.h"
#include "nodes/procedural/multiplicationExpression.h"
#include "nodes/procedural/divisionExpression.h"
#include "nodes/procedural/equalityExpression.h"
#include "nodes/procedural/nonEqualityExpression.h"
#include "nodes/procedural/logicalOrExpression.h"
#include "nodes/procedural/logicalAndExpression.h"
#include "nodes/procedural/greaterExpression.h"
#include "nodes/procedural/greaterOrEqualExpression.h"
#include "nodes/procedural/lessExpression.h"
#include "nodes/procedural/lessOrEqualExpression.h"
#include "nodes/procedural/forStatement.h"

#define TEST_DESCRIPTOR(descriptor, name, extends, bodySize) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DESCRIPTOR, descriptor->getNodeType()); \
    BOOST_CHECK_EQUAL(name, descriptor->getName()); \
    BOOST_CHECK_EQUAL(extends, descriptor->getExtends()); \
    BOOST_CHECK_EQUAL(bodySize, descriptor->getBodySize()); \
} while(0)

#define TEST_PROVISION(provision, visibility, numOfPorts) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::PROVISION, provision->getNodeType()); \
    BOOST_CHECK_EQUAL(visibility, provision->getVisibilityType()); \
    BOOST_CHECK_EQUAL(numOfPorts, provision->getNumberOfPorts()); \
} while(0)

#define TEST_REQUIREMENT(requirement, visibility, numOfPorts) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::REQUIREMENT, requirement->getNodeType()); \
    BOOST_CHECK_EQUAL(visibility, requirement->getVisibilityType()); \
    BOOST_CHECK_EQUAL(numOfPorts, requirement->getNumberOfPorts()); \
} while(0)

#define TEST_SERVICE(service, name, numOfParams, bodySize) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SERVICE, service->getNodeType()); \
    BOOST_CHECK_EQUAL(name, service->getName()); \
    BOOST_CHECK_EQUAL(numOfParams, service->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, service->getBodySize()); \
} while(0)

#define TEST_CONSTRAINT(service, name, numOfParams, bodySize) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTRAINT, constraint->getNodeType()); \
    BOOST_CHECK_EQUAL(name, constraint->getName()); \
    BOOST_CHECK_EQUAL(numOfParams, constraint->getParamsSize()); \
    BOOST_CHECK_EQUAL(bodySize, constraint->getBodySize()); \
} while(0)

#define TEST_SYMBOL(symbol, name) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SYMBOL, symbol->getNodeType()); \
    BOOST_CHECK_EQUAL(name, symbol->getStringValue()); \
} while(0)

#define TEST_CONSTANT(constant, val) \
do { \
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, constant->getNodeType()); \
    BOOST_CHECK_EQUAL(val, constant->getValue()); \
} while(0)
