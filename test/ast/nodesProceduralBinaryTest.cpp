#include <memory>

#include <boost/test/unit_test.hpp>

#include "astDefinitions.h"

BOOST_AUTO_TEST_SUITE(nodesProceduralBinaryTest)

BOOST_AUTO_TEST_CASE(additionExpression) {
    ast_addition expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::ADDITION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::PLUS, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(subtractionExpression) {
    ast_subtraction expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::SUBTRACTION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::MINUS, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(multiplicationExpression) {
    ast_multiplication expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::MULTIPLICATION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::TIMES, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(divisionExpression) {
    ast_division expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::DIVISION_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::DIVISION, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(equalityExpression) {
    ast_equality expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::EQUALITY, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(nonEqualityExpression) {
    ast_nonequality expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::NON_EQUALITY_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::NON_EQUALITY, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalOrExpression) {
    ast_or expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::LOGICAL_OR_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::LOGICAL_OR, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(logicalAndExpression) {
    ast_and expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::LOGICAL_AND_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::LOGICAL_AND, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterExpression) {
    ast_greater expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::GREATER_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::GREATER, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(greaterOrEqualExpression) {
    ast_greaterorequal expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::GREATER_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::GREATER_OR_EQUAL, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessExpression) {
    ast_less expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::LESS_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::LESS, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_CASE(lessOrEqualExpression) {
    ast_lessorequal expression(new_ptr(ast_constant)(1), new_ptr(ast_constant)(2));
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::LESS_OR_EQUAL_EXPRESSION, expression.getNodeType());
    BOOST_CHECK_EQUAL(ast::nodes::types::operatorType::LESS_OR_EQUAL, expression.getOperator());
    
    ptr(ast_constant) op1 = cast(ast_constant)(expression.getOperand1());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op1->getNodeType());
    BOOST_CHECK_EQUAL(1, op1->getValue());
    
    ptr(ast_constant) op2 = cast(ast_constant)(expression.getOperand2());
    BOOST_CHECK_EQUAL(ast::nodes::types::nodeType::CONSTANT, op2->getNodeType());
    BOOST_CHECK_EQUAL(2, op2->getValue());
}

BOOST_AUTO_TEST_SUITE_END()
