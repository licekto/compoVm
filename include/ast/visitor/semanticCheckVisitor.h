#pragma once

#include <memory>

#include "abstractVisitor.h"
#include "definitions.h"

#include "exceptions/semantic/wrongAstNodeTypeException.h"
#include "ast/semantic/globalDescriptorsTable.h"

namespace ast {

	namespace visitors {

		/**
		* \class CAbstractVisitor
		* \brief Abstract base class (interface) for other visitors.
		*
		* Abstract base class for visitors servers as interface. Every visitor derived from this one.
		*/
		class CSemanticCheckVisitor : public CAbstractVisitor, public std::enable_shared_from_this<CSemanticCheckVisitor> {
		  private:

			ptr(ast::semantic::CGlobalDescriptorTable) m_descriptorTable;

			void checkDescriptorArchitecture(std::shared_ptr<ast::nodes::compo::CDescriptor> node);

			void checkNodeType(std::shared_ptr<ast::nodes::CNode> node, ast_type type);
		  public:
                      
                        CSemanticCheckVisitor(ptr(ast::semantic::CGlobalDescriptorTable) descriptorTable = nullptr);
                      
			virtual void visit(std::shared_ptr<ast::nodes::CNode> node);
			virtual void visit(std::shared_ptr<ast::nodes::CProgram> node);

			virtual void visit(std::shared_ptr<ast::nodes::compo::CAbstractReqProv> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CAbstractServConstr> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CArchitecture> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CBind> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CCollectionPortLiteral> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CConnection> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CConstraint> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDelegation> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDereferenceLiteral> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDescriptor> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CDisconnection> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CInjectedPort> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CInterface> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CNamedPort> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CPort> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CPortAddress> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CProvision> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CRequirement> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CService> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CServiceInvocation> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CServiceSignature> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CSignaturesPort> node);
			virtual void visit(std::shared_ptr<ast::nodes::compo::CUniversalPort> node);

			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractPrimaryExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAbstractStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAdditionExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CAssignmentExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CBinaryExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CBreakStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CCompoundBody> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CConstant> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CContinueStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CDivisionExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CEqualityExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CForStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CGreaterExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CGreaterOrEqualExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CIfStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLessExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLessOrEqualExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLogicalAndExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CLogicalOrExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CMultiplicationExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CNonEqualityExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CParens> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CReturnStatement> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CSubtractionExpression> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CStringLiteral> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CSymbol> node);
			virtual void visit(std::shared_ptr<ast::nodes::procedural::CWhileStatement> node);
		};
	}
}