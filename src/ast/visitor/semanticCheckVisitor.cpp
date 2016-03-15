#include "ast/visitor/semanticCheckVisitor.h"

namespace ast {

	namespace visitors {
            
            CSemanticCheckVisitor::CSemanticCheckVisitor() {
                m_currentDescriptor = nullptr;
                m_currentService = nullptr;
            }
            
            void CSemanticCheckVisitor::checkSemantics() {
                
            }
            
            void CSemanticCheckVisitor::visit(ast::CNode *node) {}

            void CSemanticCheckVisitor::visit(ast::compo::CAbstractReqProv *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CAbstractServConstr *node) {}
            
            void CSemanticCheckVisitor::visit(ast::compo::CArchitecture *node) {
                for (size_t i = 0; i < node->getBodySize(); ++i) {
                    node->getBodyNodeAt(i)->accept(this);
                }
            }
            
            void CSemanticCheckVisitor::visit(ast::compo::CBind *node) {}
            
            void CSemanticCheckVisitor::visit(ast::compo::CCollectionPortLiteral *node) {
                
            }
            void CSemanticCheckVisitor::visit(ast::compo::CConnection *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CConstraint *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CDelegation *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CDereferenceLiteral *node) {}
            
            void CSemanticCheckVisitor::visit(ast::compo::CDescriptor *node) {
                //m_currentDescriptor = node;
                
                m_currentDescriptor->getInProvision()->accept(this);
                m_currentDescriptor->getExProvision()->accept(this);
                m_currentDescriptor->getInRequirement()->accept(this);
                m_currentDescriptor->getExRequirement()->accept(this);
                m_currentDescriptor->getArchitecture()->accept(this);
                
                for (size_t i = 0; i < m_currentDescriptor->getServicesSize(); ++i) {
                    m_currentDescriptor->getServiceAt(i)->accept(this);
                }
                
                for (size_t i = 0; i < m_currentDescriptor->getConstraintsSize(); ++i) {
                    m_currentDescriptor->getConstraintAt(i)->accept(this);
                }
            }
            
            void CSemanticCheckVisitor::visit(ast::compo::CDisconnection *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CInjectedPort *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CInterface *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CNamedPort *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CPort *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CPortAddress *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CProvision *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CRequirement *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CService *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CServiceInvocation *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CServiceSignature *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CSignaturesPort *node) {}
            void CSemanticCheckVisitor::visit(ast::compo::CUniversalPort *node) {}

            void CSemanticCheckVisitor::visit(ast::procedural::CAbstractExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CAbstractPrimaryExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CAbstractStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CAdditionExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CAssignmentExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CBinaryExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CBreakStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CCompoundBody *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CConstant *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CContinueStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CDivisionExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CEqualityExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CForStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CGreaterExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CGreaterOrEqualExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CIfStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CLessExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CLessOrEqualExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CLogicalAndExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CLogicalOrExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CMultiplicationExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CNonEqualityExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CParens *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CReturnStatement *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CSubtractionExpression *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CStringLiteral *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CSymbol *node) {}
            void CSemanticCheckVisitor::visit(ast::procedural::CWhileStatement *node) {}
            
            
	}

}
