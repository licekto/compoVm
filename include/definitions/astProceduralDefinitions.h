#pragma once

#include "ast/nodes/procedural/additionExpression.h"
#include "ast/nodes/procedural/assignmentExpression.h"
#include "ast/nodes/procedural/breakStatement.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/nodes/procedural/constant.h"
#include "ast/nodes/procedural/boolean.h"
#include "ast/nodes/procedural/continueStatement.h"
#include "ast/nodes/procedural/divisionExpression.h"
#include "ast/nodes/procedural/equalityExpression.h"
#include "ast/nodes/procedural/forStatement.h"
#include "ast/nodes/procedural/greaterExpression.h"
#include "ast/nodes/procedural/greaterOrEqualExpression.h"
#include "ast/nodes/procedural/ifStatement.h"
#include "ast/nodes/procedural/lessExpression.h"
#include "ast/nodes/procedural/lessOrEqualExpression.h"
#include "ast/nodes/procedural/logicalAndExpression.h"
#include "ast/nodes/procedural/logicalOrExpression.h"
#include "ast/nodes/procedural/multiplicationExpression.h"
#include "ast/nodes/procedural/nonEqualityExpression.h"
#include "ast/nodes/procedural/parens.h"
#include "ast/nodes/procedural/returnStatement.h"
#include "ast/nodes/procedural/stringLiteral.h"
#include "ast/nodes/procedural/subtractionExpression.h"
#include "ast/nodes/procedural/symbol.h"
#include "ast/nodes/procedural/whileStatement.h"

using ast_expression = ast::nodes::procedural::CAbstractExpression;
using ast_primaryexpression = ast::nodes::procedural::CAbstractPrimaryExpression;
using ast_statement = ast::nodes::procedural::CAbstractStatement;
using ast_addition = ast::nodes::procedural::CAdditionExpression;
using ast_assignment = ast::nodes::procedural::CAssignmentExpression;
using ast_binary = ast::nodes::procedural::CBinaryExpression;
using ast_break = ast::nodes::procedural::CBreakStatement;
using ast_compound = ast::nodes::procedural::CCompoundBody;
using ast_constant = ast::nodes::procedural::CConstant;
using ast_boolean = ast::nodes::procedural::CBoolean;
using ast_continue = ast::nodes::procedural::CContinueStatement;
using ast_division = ast::nodes::procedural::CDivisionExpression;
using ast_equality = ast::nodes::procedural::CEqualityExpression;
using ast_for = ast::nodes::procedural::CForStatement;
using ast_greater = ast::nodes::procedural::CGreaterExpression;
using ast_greaterorequal = ast::nodes::procedural::CGreaterOrEqualExpression;
using ast_if = ast::nodes::procedural::CIfStatement;
using ast_less = ast::nodes::procedural::CLessExpression;
using ast_lessorequal = ast::nodes::procedural::CLessOrEqualExpression;
using ast_and = ast::nodes::procedural::CLogicalAndExpression;
using ast_or = ast::nodes::procedural::CLogicalOrExpression;
using ast_multiplication = ast::nodes::procedural::CMultiplicationExpression;
using ast_nonequality = ast::nodes::procedural::CNonEqualityExpression;
using ast_parens = ast::nodes::procedural::CParens;
using ast_return = ast::nodes::procedural::CReturnStatement;
using ast_string = ast::nodes::procedural::CStringLiteral;
using ast_subtraction = ast::nodes::procedural::CSubtractionExpression;
using ast_symbol = ast::nodes::procedural::CSymbol;
using ast_while = ast::nodes::procedural::CWhileStatement;
