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
#include "nodes/procedural/ifStatement.h"
#include "nodes/procedural/whileStatement.h"
#include "nodes/procedural/forStatement.h"
#include "nodes/procedural/breakStatement.h"
#include "nodes/procedural/continueStatement.h"
#include "nodes/procedural/returnStatement.h"

#include "testDefinitions.h"
#include "nodes/procedural/whileStatement.h"

BOOST_AUTO_TEST_SUITE(parserProceduralTest)

// Global lexer and parser for testing purposes
Lexer lexer;
ParserWrapper parser(&lexer);

// This is very long shit-fuck, but I decided to leave it as is because binary ops should be together
BOOST_AUTO_TEST_CASE(nodesProceduralBinary) {
    // Testing input
    std::stringstream input;
    input.str("descriptor test {\
        service main() {\
            a;\
            b := 1;\
            c := 'testString';\
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 16, 0);
    
    // Check symbol
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(service->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // -------------------------------------------------------------------------
    // Check assignment
    std::shared_ptr<nodes::procedural::CAssignmentExpression> assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "b");
    
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(assignment->getRValue());
    TEST_CONSTANT(constant, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "c");
    
    // Check string literal
    std::shared_ptr<nodes::procedural::CStringLiteral> stringLiteral = std::dynamic_pointer_cast<nodes::procedural::CStringLiteral>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::STRING_LITERAL, stringLiteral->getNodeType());
    BOOST_CHECK_EQUAL("testString", stringLiteral->getValue());
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(3));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "d");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CParens> parens = std::dynamic_pointer_cast<nodes::procedural::CParens>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::PARENS, parens->getNodeType());
    
    // Check constant
    constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(parens->getExpression());
    TEST_CONSTANT(constant, 55);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(4));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "e");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CAdditionExpression> addition = std::dynamic_pointer_cast<nodes::procedural::CAdditionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ADDITION_EXPRESSION, addition->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::PLUS, addition->getOperator());
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(addition->getOperand1());
    TEST_CONSTANT(op1, 15);
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(addition->getOperand2());
    TEST_CONSTANT(op2, 64);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(5));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "f");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CSubtractionExpression> subtraction = std::dynamic_pointer_cast<nodes::procedural::CSubtractionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::SUBTRACTION_EXPRESSION, subtraction->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::MINUS, subtraction->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(subtraction->getOperand1());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONSTANT, op1->getNodeType());
    TEST_CONSTANT(op1, 18);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(subtraction->getOperand2());
    TEST_CONSTANT(op2, 2);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(6));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "g");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CMultiplicationExpression> multiplication = std::dynamic_pointer_cast<nodes::procedural::CMultiplicationExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::MULTIPLICATION_EXPRESSION, multiplication->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::TIMES, multiplication->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(multiplication->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(multiplication->getOperand2());
    TEST_CONSTANT(op2, 3);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(7));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "h");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CDivisionExpression> division = std::dynamic_pointer_cast<nodes::procedural::CDivisionExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::DIVISION_EXPRESSION, division->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::DIVISION, division->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(division->getOperand1());
    TEST_CONSTANT(op1, 10);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(division->getOperand2());
    TEST_CONSTANT(op2, 5);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(8));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "i");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CEqualityExpression> equality = std::dynamic_pointer_cast<nodes::procedural::CEqualityExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::EQUALITY_EXPRESSION, equality->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::EQUALITY, equality->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(equality->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(equality->getOperand2());
    TEST_CONSTANT(op2, 6);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(9));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "j");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CNonEqualityExpression> nonEquality = std::dynamic_pointer_cast<nodes::procedural::CNonEqualityExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::NON_EQUALITY_EXPRESSION, nonEquality->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::NON_EQUALITY, nonEquality->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(nonEquality->getOperand1());
    TEST_CONSTANT(op1, 1);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(nonEquality->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(10));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "k");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CLogicalOrExpression> logicalOr = std::dynamic_pointer_cast<nodes::procedural::CLogicalOrExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LOGICAL_OR_EXPRESSION, logicalOr->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LOGICAL_OR, logicalOr->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(logicalOr->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(logicalOr->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(11));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "l");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CLogicalAndExpression> logicalAnd = std::dynamic_pointer_cast<nodes::procedural::CLogicalAndExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LOGICAL_AND_EXPRESSION, logicalAnd->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LOGICAL_AND, logicalAnd->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(logicalAnd->getOperand1());
    TEST_CONSTANT(op1, 1);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(logicalAnd->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(12));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "m");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CLessExpression> less = std::dynamic_pointer_cast<nodes::procedural::CLessExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, less->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LESS, less->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(less->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(less->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(13));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "n");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CGreaterExpression> greater = std::dynamic_pointer_cast<nodes::procedural::CGreaterExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::GREATER_EXPRESSION, greater->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::GREATER, greater->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(greater->getOperand1());
    TEST_CONSTANT(op1, 5);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(greater->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(14));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "o");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CLessOrEqualExpression> lessOrEqual = std::dynamic_pointer_cast<nodes::procedural::CLessOrEqualExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_OR_EQUAL_EXPRESSION, lessOrEqual->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::LESS_OR_EQUAL, lessOrEqual->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(lessOrEqual->getOperand1());
    TEST_CONSTANT(op1, 0);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(lessOrEqual->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // -------------------------------------------------------------------------
    // Check assignment
    assignment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(service->getBodyNodeAt(15));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, assignment->getNodeType());
    
    // Check symbol
    symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(assignment->getVariable());
    TEST_SYMBOL(symbol, "p");
    
    // Check parens
    std::shared_ptr<nodes::procedural::CGreaterOrEqualExpression> greaterOrEqual = std::dynamic_pointer_cast<nodes::procedural::CGreaterOrEqualExpression>(assignment->getRValue());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::GREATER_OR_EQUAL_EXPRESSION, greaterOrEqual->getNodeType());
    BOOST_CHECK_EQUAL(nodes::types::operatorType::GREATER_OR_EQUAL, greaterOrEqual->getOperator());
    
    // Check constant
    op1 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(greaterOrEqual->getOperand1());
    TEST_CONSTANT(op1, 84);
    
    // Check constant
    op2 = std::dynamic_pointer_cast<nodes::procedural::CConstant>(greaterOrEqual->getOperand2());
    TEST_CONSTANT(op2, 1);
    
    // Clear parser
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_CASE(compoCompoundStatement) {
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    std::shared_ptr<nodes::procedural::CCompoundBody> compoundBody = std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    compoundBody = std::dynamic_pointer_cast<nodes::procedural::CCompoundBody>(compoundBody->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::COMPOUND_BODY, compoundBody->getNodeType());
    
    std::shared_ptr<nodes::procedural::CSymbol> symbol = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(symbol, "a");
    
    // Clear parser
    parser.clearRootNodes();
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    // Check for statement
    std::shared_ptr<nodes::procedural::CForStatement> forStatement = std::dynamic_pointer_cast<nodes::procedural::CForStatement>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::FOR, forStatement->getNodeType());
    
    // Check init expression
    std::shared_ptr<nodes::procedural::CAssignmentExpression> init = forStatement->getInitExpression();
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, init->getNodeType());
    
    // Check variable
    std::shared_ptr<nodes::procedural::CSymbol> var = init->getVariable();
    TEST_SYMBOL(var, "i");
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(init->getRValue());
    TEST_CONSTANT(constant, 1);
    
    // Check condition
    std::shared_ptr<nodes::procedural::CLessExpression> cond = std::dynamic_pointer_cast<nodes::procedural::CLessExpression>(forStatement->getCondition());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check increment
    std::shared_ptr<nodes::procedural::CAssignmentExpression> increment = std::dynamic_pointer_cast<nodes::procedural::CAssignmentExpression>(forStatement->getIncrement());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::ASSIGNMENT_EXPRESSION, init->getNodeType());
    
    // Check variable
    var = increment->getVariable();
    TEST_SYMBOL(var, "i");
    
    // Check right-hand side
    std::shared_ptr<nodes::procedural::CAdditionExpression> addition = std::dynamic_pointer_cast<nodes::procedural::CAdditionExpression>(increment->getRValue());
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(addition->getOperand1());
    TEST_SYMBOL(var, "i");
    constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(addition->getOperand2());
    TEST_CONSTANT(constant, 1);
    
    // Check body
    std::shared_ptr<nodes::procedural::CCompoundBody> compoundBody = forStatement->getBody();
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearRootNodes();
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 1, 0);
    
    // Check for statement
    std::shared_ptr<nodes::procedural::CWhileStatement> whileStatement = std::dynamic_pointer_cast<nodes::procedural::CWhileStatement>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::WHILE, whileStatement->getNodeType());
    
    // Check condition
    std::shared_ptr<nodes::procedural::CLessExpression> cond = std::dynamic_pointer_cast<nodes::procedural::CLessExpression>(whileStatement->getCondition());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    std::shared_ptr<nodes::procedural::CSymbol> var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check body
    std::shared_ptr<nodes::procedural::CCompoundBody> compoundBody = whileStatement->getBody();
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearRootNodes();
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 2, 0);
    
    // Check if statement
    std::shared_ptr<nodes::procedural::CIfStatement> ifStatement = std::dynamic_pointer_cast<nodes::procedural::CIfStatement>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    std::shared_ptr<nodes::procedural::CLessExpression> cond = std::dynamic_pointer_cast<nodes::procedural::CLessExpression>(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    std::shared_ptr<nodes::procedural::CSymbol> var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(cond->getOperand1());
    TEST_SYMBOL(var, "i");
    
    // Check constant
    std::shared_ptr<nodes::procedural::CConstant> constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(cond->getOperand2());
    TEST_CONSTANT(constant, 10);
    
    // Check if body
    std::shared_ptr<nodes::procedural::CCompoundBody> compoundBody = ifStatement->getIfBody();
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "a");
    
    // Check if else statement
    ifStatement = std::dynamic_pointer_cast<nodes::procedural::CIfStatement>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::IF, ifStatement->getNodeType());
    
    // Check condition
    cond = std::dynamic_pointer_cast<nodes::procedural::CLessExpression>(ifStatement->getCondition());
    BOOST_CHECK_EQUAL(nodes::types::nodeType::LESS_EXPRESSION, cond->getNodeType());
    
    // Check variable
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(cond->getOperand1());
    TEST_SYMBOL(var, "a");
    
    // Check constant
    constant = std::dynamic_pointer_cast<nodes::procedural::CConstant>(cond->getOperand2());
    TEST_CONSTANT(constant, 5);
    
    // Check if body
    compoundBody = ifStatement->getIfBody();
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "b");
    
    // Check else body
    compoundBody = ifStatement->getElseBody();
    var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(compoundBody->getBodyNodeAt(0));
    TEST_SYMBOL(var, "c");
    
    // Clear parser
    parser.clearRootNodes();
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
    parser.parse(input);
    
    // Check descriptor
    std::shared_ptr<nodes::compo::CDescriptor> descriptor = std::dynamic_pointer_cast<nodes::compo::CDescriptor>(parser.getRootNodeAt(0));
    TEST_DESCRIPTOR(descriptor, "test", "", 1);
    
    // Check service
    std::shared_ptr<nodes::compo::CService> service = std::dynamic_pointer_cast<nodes::compo::CService>(descriptor->getBodyNodeAt(0));
    TEST_SERVICE(service, "main", 0, 3, 0);
    
    // Check if statement
    std::shared_ptr<nodes::procedural::CBreakStatement> breakStatement = std::dynamic_pointer_cast<nodes::procedural::CBreakStatement>(service->getBodyNodeAt(0));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::BREAK, breakStatement->getNodeType());
    
    // Check if statement
    std::shared_ptr<nodes::procedural::CContinueStatement> continueStatement = std::dynamic_pointer_cast<nodes::procedural::CContinueStatement>(service->getBodyNodeAt(1));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::CONTINUE, continueStatement->getNodeType());
    
    // Check if statement
    std::shared_ptr<nodes::procedural::CReturnStatement> returnStatement = std::dynamic_pointer_cast<nodes::procedural::CReturnStatement>(service->getBodyNodeAt(2));
    BOOST_CHECK_EQUAL(nodes::types::nodeType::RETURN, returnStatement->getNodeType());
    
    // Check variable
    std::shared_ptr<nodes::procedural::CSymbol> var = std::dynamic_pointer_cast<nodes::procedural::CSymbol>(returnStatement->getExpression());
    TEST_SYMBOL(var, "a");
    
    // Clear parser
    parser.clearRootNodes();
}

BOOST_AUTO_TEST_SUITE_END()