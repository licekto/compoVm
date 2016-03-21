#pragma once

#include <memory>

namespace ast {

	namespace nodes {

		// Forward declaration
		class CNode;
		class CProgram;

		namespace compo {
			class CAbstractReqProv;
			class CAbstractServConstr;
			class CArchitecture;
			class CBind;
			class CCollectionPortLiteral;
			class CConnection;
			class CConstraint;
			class CDelegation;
			class CDereferenceLiteral;
			class CDescriptor;
			class CDisconnection;
			class CInjectedPort;
			class CInterface;
			class CNamedPort;
			class CPort;
			class CPortAddress;
			class CProvision;
			class CRequirement;
			class CService;
			class CServiceInvocation;
			class CServiceSignature;
			class CSignaturesPort;
			class CUniversalPort;
		}

		namespace procedural {
			class CAbstractExpression;
			class CAbstractPrimaryExpression;
			class CAbstractStatement;
			class CAdditionExpression;
			class CAssignmentExpression;
			class CBinaryExpression;
			class CBreakStatement;
			class CCompoundBody;
			class CConstant;
			class CContinueStatement;
			class CDivisionExpression;
			class CEqualityExpression;
			class CForStatement;
			class CGreaterExpression;
			class CGreaterOrEqualExpression;
			class CIfStatement;
			class CLessExpression;
			class CLessOrEqualExpression;
			class CLogicalAndExpression;
			class CLogicalOrExpression;
			class CMultiplicationExpression;
			class CNonEqualityExpression;
			class CParens;
			class CReturnStatement;
			class CSubtractionExpression;
			class CStringLiteral;
			class CSymbol;
			class CWhileStatement;
		}

	}

	/**
	*  \addtogroup visitors
	*  @{
	*/

	/**
	* visitors namespace to uniquely identify visitors.
	*/
	namespace visitors {

		/**
		* \class CAbstractVisitor
		* \brief Abstract base class (interface) for other visitors.
		*
		* Abstract base class for visitors servers as interface. Every visitor derived from this one.
		*/
		class CAbstractVisitor {
		  public:
			virtual void visit(std::shared_ptr<ast::nodes::CNode> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::CProgram> node) = 0;

			virtual void visit(std::shared_ptr<ast::nodes::compo::CAbstractReqProv> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CAbstractServConstr> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CArchitecture> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CBind> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CCollectionPortLiteral> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CConnection> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CConstraint> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDelegation> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDereferenceLiteral> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDescriptor> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDisconnection> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CInjectedPort> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CInterface> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CNamedPort> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CPort> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CPortAddress> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CProvision> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CRequirement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CService> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CServiceInvocation> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CServiceSignature> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CSignaturesPort> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::compo::CUniversalPort> node) = 0;

			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractPrimaryExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAdditionExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAssignmentExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CBinaryExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CBreakStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CCompoundBody> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CConstant> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CContinueStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CDivisionExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CEqualityExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CForStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CGreaterExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CGreaterOrEqualExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CIfStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLessExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLessOrEqualExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLogicalAndExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLogicalOrExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CMultiplicationExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CNonEqualityExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CParens> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CReturnStatement> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CSubtractionExpression> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CStringLiteral> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CSymbol> node) = 0;
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CWhileStatement> node) = 0;
		};
	}
}