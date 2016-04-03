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
#include "ast/nodes/compo/service.h"
#include "ast/nodes/compo/serviceInvocation.h"
#include "ast/nodes/compo/serviceSignature.h"
#include "ast/nodes/compo/signaturesPort.h"
#include "ast/nodes/compo/universalPort.h"

using ast_node = ast::nodes::CNode;
using ast_program = ast::nodes::CProgram;

using ast_descriptorinterface = ast::nodes::compo::CAbstractDescriptorInterface;
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
using ast_service = ast::nodes::compo::CService;
using ast_serviceinvocation = ast::nodes::compo::CServiceInvocation;
using ast_servicesignature = ast::nodes::compo::CServiceSignature;
using ast_signaturesport = ast::nodes::compo::CSignaturesPort;
using ast_universalport = ast::nodes::compo::CUniversalPort;