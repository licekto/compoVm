#include <memory>

#include <boost/test/unit_test.hpp>

#include "ast/procedural/additionExpression.h"
#include "ast/procedural/subtractionExpression.h"
#include "ast/procedural/multiplicationExpression.h"
#include "ast/procedural/divisionExpression.h"
#include "ast/procedural/equalityExpression.h"
#include "ast/procedural/nonEqualityExpression.h"
#include "ast/procedural/logicalOrExpression.h"
#include "ast/procedural/logicalAndExpression.h"
#include "ast/procedural/greaterExpression.h"
#include "ast/procedural/greaterOrEqualExpression.h"
#include "ast/procedural/lessExpression.h"
#include "ast/procedural/lessOrEqualExpression.h"
#include "ast/procedural/constant.h"

BOOST_AUTO_TEST_SUITE(nodesProceduralBinaryTest)

BOOST_AUTO_TEST_CASE(additionExpression) {
    ast::procedural::CAdditionExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::ADDITION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::PLUS, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(subtractionExpression) {
    ast::procedural::CSubtractionExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::SUBTRACTION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::MINUS, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(multiplicationExpression) {
    ast::procedural::CMultiplicationExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::MULTIPLICATION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::TIMES, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(divisionExpression) {
    ast::procedural::CDivisionExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::DIVISION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::DIVISION, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(equalityExpression) {
    ast::procedural::CEqualityExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::EQUALITY, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(nonEqualityExpression) {
    ast::procedural::CNonEqualityExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::NON_EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::NON_EQUALITY, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalOrExpression) {
    ast::procedural::CLogicalOrExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::LOGICAL_OR_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::LOGICAL_OR, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalAndExpression) {
    ast::procedural::CLogicalAndExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::LOGICAL_AND_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::LOGICAL_AND, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterExpression) {
    ast::procedural::CGreaterExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::GREATER_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::GREATER, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterOrEqualExpression) {
    ast::procedural::CGreaterOrEqualExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::GREATER_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::GREATER_OR_EQUAL, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessExpression) {
    ast::procedural::CLessExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::LESS_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::LESS, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessOrEqualExpression) {
    ast::procedural::CLessOrEqualExpression expression(std::make_shared<ast::procedural::CConstant>(1), std::make_shared<ast::procedural::CConstant>(2));
    BOOST_CHECK_EQUAL(ast::types::nodeType::LESS_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::types::operatorType::LESS_OR_EQUAL, expression.getOperator());
    
    std::shared_ptr<ast::procedural::CConstant> op1 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    std::shared_ptr<ast::procedural::CConstant> op2 = std::dynamic_pointer_cast<ast::procedural::CConstant>(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_SUITE_END()