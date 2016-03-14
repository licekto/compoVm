#pragma once

namespace ast {

	// Forward declaration
	class CNode;

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
		class CAssignmentExpression;
		class CBinaryExpression;
		class CBreakStatement;
		class CCompoundBody;
		class CConstant;
		class CContinueStatement;
		class CForStatement;
		class CIfStatement;
		class CParens;
		class CReturnStatement;
		class CStringLiteral;
		class CSymbol;
		class CWhileStatement;
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
			virtual void visit(ast::CNode *node) = 0;

			virtual void visit(ast::compo::CAbstractReqProv *node) = 0;
			virtual void visit(ast::compo::CAbstractServConstr *node) = 0;
			virtual void visit(ast::compo::CArchitecture *node) = 0;
			virtual void visit(ast::compo::CBind *node) = 0;
			virtual void visit(ast::compo::CCollectionPortLiteral *node) = 0;
			virtual void visit(ast::compo::CConnection *node) = 0;
			virtual void visit(ast::compo::CConstraint *node) = 0;
			virtual void visit(ast::compo::CDelegation *node) = 0;
			virtual void visit(ast::compo::CDereferenceLiteral *node) = 0;
			virtual void visit(ast::compo::CDescriptor *node) = 0;
			virtual void visit(ast::compo::CDisconnection *node) = 0;
			virtual void visit(ast::compo::CInjectedPort *node) = 0;
			virtual void visit(ast::compo::CInterface *node) = 0;
			virtual void visit(ast::compo::CNamedPort *node) = 0;
			virtual void visit(ast::compo::CPort *node) = 0;
			virtual void visit(ast::compo::CPortAddress *node) = 0;
			virtual void visit(ast::compo::CProvision *node) = 0;
			virtual void visit(ast::compo::CRequirement *node) = 0;
			virtual void visit(ast::compo::CService *node) = 0;
			virtual void visit(ast::compo::CServiceInvocation *node) = 0;
			virtual void visit(ast::compo::CServiceSignature *node) = 0;
			virtual void visit(ast::compo::CSignaturesPort *node) = 0;
			virtual void visit(ast::compo::CUniversalPort *node) = 0;

			virtual void visit(ast::procedural::CAbstractExpression *node) = 0;
			virtual void visit(ast::procedural::CAbstractPrimaryExpression *node) = 0;
			virtual void visit(ast::procedural::CAbstractStatement *node) = 0;
			virtual void visit(ast::procedural::CAssignmentExpression *node) = 0;
			virtual void visit(ast::procedural::CBinaryExpression *node) = 0;
			virtual void visit(ast::procedural::CBreakStatement *node) = 0;
			virtual void visit(ast::procedural::CCompoundBody *node) = 0;
			virtual void visit(ast::procedural::CConstant *node) = 0;
			virtual void visit(ast::procedural::CContinueStatement *node) = 0;
			virtual void visit(ast::procedural::CForStatement *node) = 0;
			virtual void visit(ast::procedural::CIfStatement *node) = 0;
			virtual void visit(ast::procedural::CParens *node) = 0;
			virtual void visit(ast::procedural::CReturnStatement *node) = 0;
			virtual void visit(ast::procedural::CStringLiteral *node) = 0;
			virtual void visit(ast::procedural::CSymbol *node) = 0;
			virtual void visit(ast::procedural::CWhileStatement *node) = 0;
		};
	}
}