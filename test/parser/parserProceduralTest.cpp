#include <iostream>
#include <vector>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "parser/lexer.h"
#include "parser/parserWrapper.h"

#include "definitions/allDefinitions.h"
#include "testDefinitions.h"

BOOST_AUTO_TEST_SUITE(parserProceduralTest)

// Global lexer and parser for testing purposes
ParserWrapper parser(new_ptr(Lexer)());

BOOST_AUTO_TEST_CASE(unsignedTest) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            |a b|\
            a := -1;\
            b := -256;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 2, 2);
    
    // Check assignment
    ptr(ast_assignment) assignment = cast(ast_assignment)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    ptr(ast_symbol) symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "a");
    
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(assignment->getRightSide());
    TEST_CONSTANT(constant, -1);
    
        // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    
    // Check constant
    constant = cast(ast_constant)(assignment->getRightSide());
    TEST_CONSTANT(constant, -256);
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(booleanTest) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            |a b|\
            a := true;\
            b := false;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 2, 2);
    
    // Check assignment
    ptr(ast_assignment) assignment = cast(ast_assignment)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    ptr(ast_symbol) symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "a");
    
    
    // Check constant
    ptr(ast_boolean) constant = cast(ast_boolean)(assignment->getRightSide());
    TEST_BOOL(constant, true);
    
        // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    
    // Check constant
    constant = cast(ast_boolean)(assignment->getRightSide());
    TEST_BOOL(constant, false);
    
    // Clear parser
    parser.clearAll();
}

// This is very long shit-fuck, but I decided to leave it as is because binary ops should be together
BOOST_AUTO_TEST_CASE(nodesProceduralBinary) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            a;\
            b := 1;\
            c := \"testString\";\
            d := (55);\
            e := 15 + 64;\
            f := 18 - 2;\
            g := 5 * 3;\
            h := 10 / 5;\
            i := 5 == 6;\
            j := 1 != 1;\
            k := 0 || 1;\
            l := 1 && 1;\
            m := 0 < 1;\
            n := 5 > 1;\
            o := 0 <= 1;\
            p := 84 >= 1;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 16, 0);
    
    // Check symbol
    ptr(ast_symbol) symbol = cast(ast_symbol)(service->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // -------------------------------------------------------------------------
    // Check assignment
    ptr(ast_assignment) assignment = cast(ast_assignment)(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(assignment->getRightSide());
    TEST_CONSTANT(constant, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "c");
    
    // Check string literal
    ptr(ast_string) stringLiteral = cast(ast_string)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::STRING_LITERAL, stringLiteral->getNodeType());
    BOOST_CHECK_EQUAL("testString", stringLiteral->getValue());
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "d");
    
    // Check parens
    ptr(ast_parens) parens = cast(ast_parens)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::PARENS, parens->getNodeType());
    
    // Check constant
    constant = cast(ast_constant)(parens->getExpression());
    TEST_CONSTANT(constant, 55);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(4));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "e");
    
    // Check parens
    ptr(ast_addition) addition = cast(ast_addition)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::ADDITION_EXPRESSION, addition->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::PLUS, addition->getOperator());
    
    // Check constant
    ptr(ast_constant) op1 = cast(ast_constant)(addition->getOperand1());
    TEST_CONSTANT(op1, 15);
    
    // Check constant
    ptr(ast_constant) op2 = cast(ast_constant)(addition->getOperand2());
    TEST_CONSTANT(op2, 64);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(5));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "f");
    
    // Check parens
    ptr(ast_subtraction) subtraction = cast(ast_subtraction)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::SUBTRACTION_EXPRESSION, subtraction->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::MINUS, subtraction->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(subtraction->getOperand1());
    BOOST_CHECK_EQUAL(types::nodeType::CONSTANT, op1->getNodeType());
    TEST_CONSTANT(op1, 18);
    
    // Check constant
    op2 = cast(ast_constant)(subtraction->getOperand2());
    TEST_CONSTANT(op2, 2);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(6));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "g");
    
    // Check parens
    ptr(ast_multiplication) multiplication = cast(ast_multiplication)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::MULTIPLICATION_EXPRESSION, multiplication->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::TIMES, multiplication->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(multiplication->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = cast(ast_constant)(multiplication->getOperand2());
    TEST_CONSTANT(op2, 3);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(7));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "h");
    
    // Check parens
    ptr(ast_division) division = cast(ast_division)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::DIVISION_EXPRESSION, division->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::DIVISION, division->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(division->getOperand1());
    TEST_CONSTANT(op1, 10);
    
    // Check constant
    op2 = cast(ast_constant)(division->getOperand2());
    TEST_CONSTANT(op2, 5);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(8));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "i");
    
    // Check parens
    ptr(ast_equality) equality = cast(ast_equality)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::EQUALITY_EXPRESSION, equality->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::EQUALITY, equality->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(equality->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = cast(ast_constant)(equality->getOperand2());
    TEST_CONSTANT(op2, 6);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(9));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "j");
    
    // Check parens
    ptr(ast_nonequality) nonEquality = cast(ast_nonequality)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::NON_EQUALITY_EXPRESSION, nonEquality->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::NON_EQUALITY, nonEquality->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(nonEquality->getOperand1());
    TEST_CONSTANT(op1, 1);
    
    // Check constant
    op2 = cast(ast_constant)(nonEquality->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(10));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "k");
    
    // Check parens
    ptr(ast_or) logicalOr = cast(ast_or)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::LOGICAL_OR_EXPRESSION, logicalOr->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::LOGICAL_OR, logicalOr->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(logicalOr->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = cast(ast_constant)(logicalOr->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(11));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "l");
    
    // Check parens
    ptr(ast_and) logicalAnd = cast(ast_and)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::LOGICAL_AND_EXPRESSION, logicalAnd->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::LOGICAL_AND, logicalAnd->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(logicalAnd->getOperand1());
    TEST_CONSTANT(op1, 1);
    
    // Check constant
    op2 = cast(ast_constant)(logicalAnd->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(12));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "m");
    
    // Check parens
    ptr(ast_less) less = cast(ast_less)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, less->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::LESS, less->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(less->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = cast(ast_constant)(less->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(13));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "n");
    
    // Check parens
    ptr(ast_greater) greater = cast(ast_greater)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::GREATER_EXPRESSION, greater->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::GREATER, greater->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(greater->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = cast(ast_constant)(greater->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(14));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "o");
    
    // Check parens
    ptr(ast_lessorequal) lessOrEqual = cast(ast_lessorequal)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_OR_EQUAL_EXPRESSION, lessOrEqual->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::LESS_OR_EQUAL, lessOrEqual->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(lessOrEqual->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = cast(ast_constant)(lessOrEqual->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = cast(ast_assignment)(service->getBodyNodeAt(15));
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = cast(ast_symbol)(assignment->getVariable());
    TEST_SYMBOL(symbol, "p");
    
    // Check parens
    ptr(ast_greaterorequal) greaterOrEqual = cast(ast_greaterorequal)(assignment->getRightSide());
    BOOST_CHECK_EQUAL(types::nodeType::GREATER_OR_EQUAL_EXPRESSION, greaterOrEqual->getNodeType());
    BOOST_CHECK_EQUAL(types::operatorType::GREATER_OR_EQUAL, greaterOrEqual->getOperator());
    
    // Check constant
    op1 = cast(ast_constant)(greaterOrEqual->getOperand1());
    TEST_CONSTANT(op1, 84);
    
    // Check constant
    op2 = cast(ast_constant)(greaterOrEqual->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesCompoundStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            {\
                {\
                    {\
                        {\
                            a;\
                        }\
                    }\
                }\
            }\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    ptr(ast_compound) compoundBody = cast(ast_compound)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = cast(ast_compound)(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = cast(ast_compound)(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = cast(ast_compound)(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    ptr(ast_symbol) symbol = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesForStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            for (i := 1; i < 10; i := i + 1) {\
                a;\
            }\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    // Check for statement
    ptr(ast_for) forStatement = cast(ast_for)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::FOR, forStatement->getNodeType());
    
    // Check init expression
    ptr(ast_assignment) init = forStatement->getInitExpression();
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, init->getNodeType());
    
    // Check variable
    ptr(ast_symbol) var = init->getVariable();
    TEST_SYMBOL(var, "i");
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(init->getRightSide());
    TEST_CONSTANT(constant, 1);
    
    // Check condition
    ptr(ast_less) cond = cast(ast_less)(forStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    var = cast(ast_symbol)(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    constant = cast(ast_constant)(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check increment
    ptr(ast_assignment) increment = cast(ast_assignment)(forStatement->getIncrement());
    BOOST_CHECK_EQUAL(types::nodeType::ASSIGNMENT_EXPRESSION, init->getNodeType());
    
    // Check variable
    var = increment->getVariable();
    TEST_SYMBOL(var, "i");
    
    // Check right-hand side
    ptr(ast_addition) addition = cast(ast_addition)(increment->getRightSide());
    var = cast(ast_symbol)(addition->getOperand1());
    TEST_SYMBOL(var, "i");
    constant = cast(ast_constant)(addition->getOperand2());
    TEST_CONSTANT(constant, 1);
    
    // Check body
    ptr(ast_compound) compoundBody = forStatement->getBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesWhileStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            while(i < 10) {\
                a;\
            }\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    // Check for statement
    ptr(ast_while) whileStatement = cast(ast_while)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::WHILE, whileStatement->getNodeType());
    
    // Check condition
    ptr(ast_less) cond = cast(ast_less)(whileStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    ptr(ast_symbol) var = cast(ast_symbol)(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check body
    ptr(ast_compound) compoundBody = whileStatement->getBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesIfStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            if (i < 10) {\
                a;\
            }\
            if (a < 5) {\
                b;\
            } else {\
                c;\
            }\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 2, 0);
    
    // Check if statement
    ptr(ast_if) ifStatement = cast(ast_if)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    ptr(ast_less) cond = cast(ast_less)(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    ptr(ast_symbol) var = cast(ast_symbol)(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check if body
    ptr(ast_compound) compoundBody = ifStatement->getIfBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Check if else statement
    ifStatement = cast(ast_if)(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    cond = cast(ast_less)(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    var = cast(ast_symbol)(cond->getOperand1());
    TEST_SYMBOL(var, "a");
    
    // Check constant
    constant = cast(ast_constant)(cond->getOperand2());
    TEST_CONSTANT(constant, 5);
    
    // Check if body
    compoundBody = ifStatement->getIfBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "b");
    
    // Check else body
    compoundBody = cast(ast_compound)(ifStatement->getElseBody());
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "c");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesElseIfStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            if (a < 5) {\
                b;\
            } else if (a == 10) {\
                c;\
            }\
        }\
    }");
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    // Check if statement
    ptr(ast_if) ifStatement = cast(ast_if)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    ptr(ast_less) cond = cast(ast_less)(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    ptr(ast_symbol) var = cast(ast_symbol)(cond->getOperand1());
    TEST_SYMBOL(var, "a");
    
    // Check constant
    ptr(ast_constant) constant = cast(ast_constant)(cond->getOperand2());
    TEST_CONSTANT(constant, 5);
    
    // Check if body
    ptr(ast_compound) compoundBody = ifStatement->getIfBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "b");
    
    // Check else if body
    ifStatement = cast(ast_if)(ifStatement->getElseBody());
    BOOST_CHECK_EQUAL(types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    ptr(ast_equality) eq = cast(ast_equality)(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(types::nodeType::EQUALITY_EXPRESSION, eq->getNodeType());
    
    // Check variable
    var = cast(ast_symbol)(eq->getOperand1());
    TEST_SYMBOL(var, "a");
    
    // Check constant
    constant = cast(ast_constant)(eq->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check if body
    compoundBody = ifStatement->getIfBody();
    var = cast(ast_symbol)(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "c");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(nodesBreakContinueReturnStatement) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            break;\
            continue;\
            return a;\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 3, 0);
    
    // Check if statement
    ptr(ast_break) breakStatement = cast(ast_break)(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(types::nodeType::BREAK, breakStatement->getNodeType());
    
    // Check if statement
    ptr(ast_continue) continueStatement = cast(ast_continue)(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(types::nodeType::CONTINUE, continueStatement->getNodeType());
    
    // Check if statement
    ptr(ast_return) returnStatement = cast(ast_return)(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(types::nodeType::RETURN, returnStatement->getNodeType());
    
    // Check variable
    ptr(ast_symbol) var = cast(ast_symbol)(returnStatement->getExpression());
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearAll();
}

BOOST_AUTO_TEST_CASE(comments) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            /*This is comment*/\
        }\
    }");
    
    // Parse input and create AST
    parser.parseAll(input);
    
    // Check descriptor
    ptr(ast_descriptor) descriptor = cast(ast_descriptor)(parser.getRootNode()->getNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 0, 1, 0);
    
    // Check service
    ptr(ast_service) service = cast(ast_service)(descriptor->getServiceAt(0));
    TEST_SERVICE(service, "main", 0, 0, 0);
    
    // Clear parser
    parser.clearAll();
}
BOOST_AUTO_TEST_SUITE_END()
