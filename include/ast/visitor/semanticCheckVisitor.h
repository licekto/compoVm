#pragma once

#include "abstractVisitor.h"
#include "definitions.h"

#include "exceptions/semantic/wrongAstNodeTypeException.h"

namespace ast {

	namespace visitors {

		/**
		* \class CAbstractVisitor
		* \brief Abstract base class (interface) for other visitors.
		*
		* Abstract base class for visitors servers as interface. Every visitor derived from this one.
		*/
		class CSemanticCheckVisitor : public CAbstractVisitor {
                  private:
                    
                        void checkDescriptor();
                      
                        void checkNodeType(ast::CNode *node, ast_type type);
		  public:                        
			virtual void visit(ast::CNode *node);
                        virtual void visit(ast::CProgram *node);

			virtual void visit(ast::compo::CAbstractReqProv *node);
			virtual void visit(ast::compo::CAbstractServConstr *node);
			virtual void visit(ast::compo::CArchitecture *node);
			virtual void visit(ast::compo::CBind *node);
			virtual void visit(ast::compo::CCollectionPortLiteral *node);
			virtual void visit(ast::compo::CConnection *node);
			virtual void visit(ast::compo::CConstraint *node);
			virtual void visit(ast::compo::CDelegation *node);
			virtual void visit(ast::compo::CDereferenceLiteral *node);
			virtual void visit(ast::compo::CDescriptor *node);
			virtual void visit(ast::compo::CDisconnection *node);
			virtual void visit(ast::compo::CInjectedPort *node);
			virtual void visit(ast::compo::CInterface *node);
			virtual void visit(ast::compo::CNamedPort *node);
			virtual void visit(ast::compo::CPort *node);
			virtual void visit(ast::compo::CPortAddress *node);
			virtual void visit(ast::compo::CProvision *node);
			virtual void visit(ast::compo::CRequirement *node);
			virtual void visit(ast::compo::CService *node);
			virtual void visit(ast::compo::CServiceInvocation *node);
			virtual void visit(ast::compo::CServiceSignature *node);
			virtual void visit(ast::compo::CSignaturesPort *node);
			virtual void visit(ast::compo::CUniversalPort *node);

			virtual void visit(ast::procedural::CAbstractExpression *node);
			virtual void visit(ast::procedural::CAbstractPrimaryExpression *node);
			virtual void visit(ast::procedural::CAbstractStatement *node);
			virtual void visit(ast::procedural::CAdditionExpression *node);
			virtual void visit(ast::procedural::CAssignmentExpression *node);
			virtual void visit(ast::procedural::CBinaryExpression *node);
			virtual void visit(ast::procedural::CBreakStatement *node);
			virtual void visit(ast::procedural::CCompoundBody *node);
			virtual void visit(ast::procedural::CConstant *node);
			virtual void visit(ast::procedural::CContinueStatement *node);
			virtual void visit(ast::procedural::CDivisionExpression *node);
			virtual void visit(ast::procedural::CEqualityExpression *node);
			virtual void visit(ast::procedural::CForStatement *node);
			virtual void visit(ast::procedural::CGreaterExpression *node);
			virtual void visit(ast::procedural::CGreaterOrEqualExpression *node);
			virtual void visit(ast::procedural::CIfStatement *node);
			virtual void visit(ast::procedural::CLessExpression *node);
			virtual void visit(ast::procedural::CLessOrEqualExpression *node);
			virtual void visit(ast::procedural::CLogicalAndExpression *node);
			virtual void visit(ast::procedural::CLogicalOrExpression *node);
			virtual void visit(ast::procedural::CMultiplicationExpression *node);
			virtual void visit(ast::procedural::CNonEqualityExpression *node);
			virtual void visit(ast::procedural::CParens *node);
			virtual void visit(ast::procedural::CReturnStatement *node);
			virtual void visit(ast::procedural::CSubtractionExpression *node);
			virtual void visit(ast::procedural::CStringLiteral *node);
			virtual void visit(ast::procedural::CSymbol *node);
			virtual void visit(ast::procedural::CWhileStatement *node);
		};
	}
}