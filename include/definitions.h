#pragma once

#include <memory>

#include "ast/nodes/node.h"
#include "ast/nodes/program.h"

#include "ast/nodes/compo/architecture.h"
#include "ast/nodes/compo/collectionPortLiteral.h"
#include "ast/nodes/compo/connection.h"
#include "ast/nodes/compo/constraint.h"
#include "ast/nodes/compo/delegation.h"
#include "ast/nodes/compo/dereferenceLiteral.h"
#include "ast/nodes/compo/descriptor.h"
#include "ast/nodes/compo/disconnection.h"
#include "ast/nodes/compo/injectedPort.h"
#include "ast/nodes/compo/interface.h"
#include "ast/nodes/compo/namedPort.h"
#include "ast/nodes/compo/portAddress.h"
#include "ast/nodes/compo/provision.h"
#include "ast/nodes/compo/requirement.h"
#include "ast/nodes/compo/service.h"
#include "ast/nodes/compo/serviceInvocation.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/compo/signaturesPort.h"
#include "ast/nodes/compo/universalPort.h"

#include "ast/nodes/procedural/additionExpression.h"
#include "ast/nodes/procedural/assignmentExpression.h"
#include "ast/nodes/procedural/breakStatement.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/nodes/procedural/constant.h"
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

#include "ast/nodes/types/nodeType.h"

using ast_node = ast::nodes::CNode;
using ast_program = ast::nodes::CProgram;

using ast_reqprov = ast::nodes::compo::CAbstractReqProv;
using ast_servconstr = ast::nodes::compo::CAbstractServConstr;
using ast_architecture = ast::nodes::compo::CArchitecture;
using ast_bind = ast::nodes::compo::CBind;
using ast_collectionportliteral = ast::nodes::compo::CCollectionPortLiteral;
using ast_connection = ast::nodes::compo::CConnection;
using ast_constraint = ast::nodes::compo::CConstraint;
using ast_delegation = ast::nodes::compo::CDelegation;
using ast_dereference = ast::nodes::compo::CDereferenceLiteral;
using ast_descriptor = ast::nodes::compo::CDescriptor;
using ast_disconnection = ast::nodes::compo::CDisconnection;
using ast_injectedport = ast::nodes::compo::CInjectedPort;
using ast_interface = ast::nodes::compo::CInterface;
using ast_namedport = ast::nodes::compo::CNamedPort;
using ast_port = ast::nodes::compo::CPort;
using ast_portaddress = ast::nodes::compo::CPortAddress;
using ast_provision = ast::nodes::compo::CProvision;
using ast_requirement = ast::nodes::compo::CRequirement;
using ast_service = ast::nodes::compo::CService;
using ast_serviceinvocation = ast::nodes::compo::CServiceInvocation;
using ast_servicesignature = ast::nodes::compo::CServiceSignature;
using ast_signaturesport = ast::nodes::compo::CSignaturesPort;
using ast_universalport = ast::nodes::compo::CUniversalPort;


using ast_expression = ast::nodes::procedural::CAbstractExpression;
using ast_primaryexpression = ast::nodes::procedural::CAbstractPrimaryExpression;
using ast_statement = ast::nodes::procedural::CAbstractStatement;
using ast_addition = ast::nodes::procedural::CAdditionExpression;
using ast_assignment = ast::nodes::procedural::CAssignmentExpression;
using ast_binary = ast::nodes::procedural::CBinaryExpression;
using ast_break = ast::nodes::procedural::CBreakStatement;
using ast_compound = ast::nodes::procedural::CCompoundBody;
using ast_constant = ast::nodes::procedural::CConstant;
using ast_continue = ast::nodes::procedural::CContinueStatement;
using ast_division = ast::nodes::procedural::CDivisionExpression;
using ast_equality = ast::nodes::procedural::CEqualityExpression;
using ast_for = ast::nodes::procedural::CForStatement;
using ast_greater = ast::nodes::procedural::CGreaterExpression;
using ast_greaterorequal = ast::nodes::procedural::CGreaterOrEqualExpression ;
using ast_if = ast::nodes::procedural::CIfStatement ;
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

using ast_type = ast::nodes::types::nodeType;

#define ptr(x) std::shared_ptr<x>
#define new_ptr(x) std::make_shared<x>
#define cast(x) std::dynamic_pointer_cast<x>