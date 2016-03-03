#include <memory>

#include <boost/test/unit_test.hpp>

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
#include "nodes/procedural/constant.h"

BOOST_AUTO_TEST_SUITE(nodesProceduralBinaryTest)

BOOST_AUTO_TEST_CASE(additionExpression) {
    nodes::procedural::CAdditionExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ADDITION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::PLUS, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(subtractionExpression) {
    nodes::procedural::CSubtractionExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SUBTRACTION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::MINUS, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(multiplicationExpression) {
    nodes::procedural::CMultiplicationExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::MULTIPLICATION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::TIMES, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(divisionExpression) {
    nodes::procedural::CDivisionExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DIVISION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::DIVISION, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(equalityExpression) {
    nodes::procedural::CEqualityExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::EQUALITY, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(nonEqualityExpression) {
    nodes::procedural::CNonEqualityExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::NON_EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::NON_EQUALITY, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalOrExpression) {
    nodes::procedural::CLogicalOrExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LOGICAL_OR_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LOGICAL_OR, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalAndExpression) {
    nodes::procedural::CLogicalAndExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LOGICAL_AND_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LOGICAL_AND, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterExpression) {
    nodes::procedural::CGreaterExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::GREATER_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::GREATER, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterOrEqualExpression) {
    nodes::procedural::CGreaterOrEqualExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::GREATER_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::GREATER_OR_EQUAL, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessExpression) {
    nodes::procedural::CLessExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LESS, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessOrEqualExpression) {
    nodes::procedural::CLessOrEqualExpression expression(std::make_shared<nodes::procedural::CConstant>(1), std::make_shared<nodes::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LESS_OR_EQUAL, expression.getOperator());
    
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_SUITE_END()