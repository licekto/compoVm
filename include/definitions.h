#pragma once

#include <memory>

#include "ast/node.h"
#include "ast/program.h"

#include "ast/compo/architecture.h"
#include "ast/compo/collectionPortLiteral.h"
#include "ast/compo/connection.h"
#include "ast/compo/constraint.h"
#include "ast/compo/delegation.h"
#include "ast/compo/dereferenceLiteral.h"
#include "ast/compo/descriptor.h"
#include "ast/compo/disconnection.h"
#include "ast/compo/injectedPort.h"
#include "ast/compo/interface.h"
#include "ast/compo/namedPort.h"
#include "ast/compo/portAddress.h"
#include "ast/compo/provision.h"
#include "ast/compo/requirement.h"
#include "ast/compo/service.h"
#include "ast/compo/serviceInvocation.h"
#include "ast/compo/serviceSignature.h"
#include "ast/compo/signaturesPort.h"
#include "ast/compo/universalPort.h"

#include "ast/procedural/additionExpression.h"
#include "ast/procedural/assignmentExpression.h"
#include "ast/procedural/breakStatement.h"
#include "ast/procedural/compoundBody.h"
#include "ast/procedural/constant.h"
#include "ast/procedural/continueStatement.h"
#include "ast/procedural/divisionExpression.h"
#include "ast/procedural/equalityExpression.h"
#include "ast/procedural/forStatement.h"
#include "ast/procedural/greaterExpression.h"
#include "ast/procedural/greaterOrEqualExpression.h"
#include "ast/procedural/ifStatement.h"
#include "ast/procedural/lessExpression.h"
#include "ast/procedural/lessOrEqualExpression.h"
#include "ast/procedural/logicalAndExpression.h"
#include "ast/procedural/logicalOrExpression.h"
#include "ast/procedural/multiplicationExpression.h"
#include "ast/procedural/nonEqualityExpression.h"
#include "ast/procedural/parens.h"
#include "ast/procedural/returnStatement.h"
#include "ast/procedural/stringLiteral.h"
#include "ast/procedural/subtractionExpression.h"
#include "ast/procedural/symbol.h"
#include "ast/procedural/whileStatement.h"

using ast_node = ast::CNode;

using ast_reqprov = ast::compo::CAbstractReqProv;
using ast_servconstr = ast::compo::CAbstractServConstr;
using ast_architecture = ast::compo::CArchitecture;
using ast_bind = ast::compo::CBind;
using ast_collectionportliteral = ast::compo::CCollectionPortLiteral;
using ast_connection = ast::compo::CConnection;
using ast_constraint = ast::compo::CConstraint;
using ast_delegation = ast::compo::CDelegation;
using ast_dereference = ast::compo::CDereferenceLiteral;
using ast_descriptor = ast::compo::CDescriptor;
using ast_disconnection = ast::compo::CDisconnection;
using ast_injectedport = ast::compo::CInjectedPort;
using ast_interface = ast::compo::CInterface;
using ast_namedport = ast::compo::CNamedPort;
using ast_port = ast::compo::CPort;
using ast_portaddress = ast::compo::CPortAddress;
using ast_provision = ast::compo::CProvision;
using ast_requirement = ast::compo::CRequirement;
using ast_service = ast::compo::CService;
using ast_serviceinvocation = ast::compo::CServiceInvocation;
using ast_servicesignature = ast::compo::CServiceSignature;
using ast_signaturesport = ast::compo::CSignaturesPort;
using ast_universalport = ast::compo::CUniversalPort;


using ast_expression = ast::procedural::CAbstractExpression;
using ast_primaryexpression = ast::procedural::CAbstractPrimaryExpression;
using ast_statement = ast::procedural::CAbstractStatement;
using ast_addition = ast::procedural::CAdditionExpression;
using ast_assignment = ast::procedural::CAssignmentExpression;
using ast_binary = ast::procedural::CBinaryExpression;
using ast_break = ast::procedural::CBreakStatement;
using ast_compound = ast::procedural::CCompoundBody;
using ast_constant = ast::procedural::CConstant;
using ast_continue = ast::procedural::CContinueStatement;
using ast_division = ast::procedural::CDivisionExpression;
using ast_equality = ast::procedural::CEqualityExpression;
using ast_for = ast::procedural::CForStatement;
using ast_greater = ast::procedural::CGreaterExpression;
using ast_greaterorequal = ast::procedural::CGreaterOrEqualExpression ;
using ast_if = ast::procedural::CIfStatement ;
using ast_less = ast::procedural::CLessExpression;
using ast_lessorequal = ast::procedural::CLessOrEqualExpression;
using ast_and = ast::procedural::CLogicalAndExpression;
using ast_or = ast::procedural::CLogicalOrExpression;
using ast_multiplication = ast::procedural::CMultiplicationExpression;
using ast_nonequality = ast::procedural::CNonEqualityExpression;
using ast_parens = ast::procedural::CParens;
using ast_return = ast::procedural::CReturnStatement;
using ast_string = ast::procedural::CStringLiteral;
using ast_subtraction = ast::procedural::CSubtractionExpression;
using ast_symbol = ast::procedural::CSymbol;
using ast_while = ast::procedural::CWhileStatement;

#define ptr(x) std::shared_ptr<x>
#define new_ptr(x) std::make_shared<x>
#define cast(x) std::dynamic_pointer_cast<x>