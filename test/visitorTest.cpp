#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "testDefinitions.h"

#include "ast/visitor/abstractVisitor.h"
#include "ast/compo/architecture.h"
#include "ast/compo/provision.h"
#include "ast/compo/requirement.h"
#include "ast/compo/constraint.h"
#include "ast/compo/connection.h"
#include "ast/compo/disconnection.h"

BOOST_AUTO_TEST_SUITE(visitorTest)

class testVisitor : public ast::visitors::CAbstractVisitor {
    
    private:
        std::string nodes;
    
    public:
        
        virtual void visit(ast::CNode */* node */) {nodes += " CNode";}

        virtual void visit(ast::compo::CAbstractReqProv */* node */) {nodes += " CAbstractReqProv";}
        virtual void visit(ast::compo::CAbstractServConstr */* node */) {nodes += " CAbstractServConstr";}
        virtual void visit(ast::compo::CArchitecture */* node */) {nodes += " CArchitecture";}
        virtual void visit(ast::compo::CBind */* node */) {nodes += " CBind";}
        virtual void visit(ast::compo::CCollectionPortLiteral */* node */) {nodes += " CCollectionPortLiteral";}
        virtual void visit(ast::compo::CConnection */* node */) {nodes += " CConnection";}
        virtual void visit(ast::compo::CConstraint */* node */) {nodes += " CConstraint";}
        virtual void visit(ast::compo::CDelegation */* node */) {nodes += " CDelegation";}
        virtual void visit(ast::compo::CDereferenceLiteral */* node */) {nodes += " CDereferenceLiteral";}
        virtual void visit(ast::compo::CDescriptor */* node */) {nodes += " CDescriptor";}
        virtual void visit(ast::compo::CDisconnection */* node */) {nodes += " CDisconnection";}
        virtual void visit(ast::compo::CInjectedPort */* node */) {nodes += " CInjectedPort";}
        virtual void visit(ast::compo::CInterface */* node */) {nodes += " CInterface";}
        virtual void visit(ast::compo::CNamedPort */* node */) {nodes += " CNamedPort";}
        virtual void visit(ast::compo::CPort */* node */) {nodes += " CPort";}
        virtual void visit(ast::compo::CPortAddress */* node */) {nodes += " CPortAddress";}
        virtual void visit(ast::compo::CProvision */* node */) {nodes += " CProvision";}
        virtual void visit(ast::compo::CRequirement */* node */) {nodes += " CRequirement";}
        virtual void visit(ast::compo::CService */* node */) {nodes += " CService";}
        virtual void visit(ast::compo::CServiceInvocation */* node */) {nodes += " CServiceInvocation";}
        virtual void visit(ast::compo::CServiceSignature */* node */) {nodes += " CServiceSignature";}
        virtual void visit(ast::compo::CSignaturesPort */* node */) {nodes += " CSignaturesPort";}
        virtual void visit(ast::compo::CUniversalPort */* node */) {nodes += " CUniversalPort";}

        virtual void visit(ast::procedural::CAbstractExpression */* node */) {nodes += " CAbstractExpression";}
        virtual void visit(ast::procedural::CAbstractPrimaryExpression */* node */) {nodes += " CAbstractPrimaryExpression";}
        virtual void visit(ast::procedural::CAbstractStatement */* node */) {nodes += " CAbstractStatement";}
        virtual void visit(ast::procedural::CAdditionExpression * /* node */) {nodes += " CAdditionExpression";}
        virtual void visit(ast::procedural::CAssignmentExpression */* node */) {nodes += " CAssignmentExpression";}
        virtual void visit(ast::procedural::CBinaryExpression */* node */) {nodes += " CBinaryExpression";}
        virtual void visit(ast::procedural::CBreakStatement */* node */) {nodes += " CBreakStatement";}
        virtual void visit(ast::procedural::CCompoundBody */* node */) {nodes += " CCompoundBody";}
        virtual void visit(ast::procedural::CConstant */* node */) {nodes += " CConstant";}
        virtual void visit(ast::procedural::CContinueStatement */* node */) {nodes += " CContinueStatement";}
        virtual void visit(ast::procedural::CDivisionExpression * /* node */) {nodes += " CDivisionExpression";}
        virtual void visit(ast::procedural::CEqualityExpression * /* node */) {nodes += " CEqualityExpression";}
        virtual void visit(ast::procedural::CForStatement */* node */) {nodes += " CForStatement";}
        virtual void visit(ast::procedural::CGreaterExpression * /* node */) {nodes += " CGreaterExpression";}
        virtual void visit(ast::procedural::CGreaterOrEqualExpression * /* node */) {nodes += " CGreaterOrEqualExpression";}
        virtual void visit(ast::procedural::CIfStatement */* node */) {nodes += " CIfStatement";}
        virtual void visit(ast::procedural::CLessExpression * /* node */) {nodes += " CLessExpression";}
        virtual void visit(ast::procedural::CLessOrEqualExpression * /* node */) {nodes += " CLessOrEqualExpression";}
        virtual void visit(ast::procedural::CLogicalAndExpression * /* node */) {nodes += " CLogicalAndExpression";}
        virtual void visit(ast::procedural::CLogicalOrExpression * /* node */) {nodes += " CLogicalOrExpression";}
        virtual void visit(ast::procedural::CMultiplicationExpression * /* node */) {nodes += " CMultiplicationExpression";}
        virtual void visit(ast::procedural::CNonEqualityExpression * /* node */) {nodes += " CNonEqualityExpression";}
        virtual void visit(ast::procedural::CParens */* node */) {nodes += " CParens";}
        virtual void visit(ast::procedural::CReturnStatement */* node */) {nodes += " CReturnStatement";}
        virtual void visit(ast::procedural::CSubtractionExpression * /* node */) {nodes += " CSubtractionExpression";}
        virtual void visit(ast::procedural::CStringLiteral */* node */) {nodes += " CStringLiteral";}
        virtual void visit(ast::procedural::CSymbol */* node */) {nodes += " CSymbol";}
        virtual void visit(ast::procedural::CWhileStatement */* node */) {nodes += " CWhileStatement";}
        
        std::string getNodes() const {
            return nodes;
        }
};

BOOST_AUTO_TEST_CASE(basic) {
    
    testVisitor visitor;
    
    ast::compo::CDescriptor descriptor;
    descriptor.accept(&visitor);
    
    ast::compo::CArchitecture architecture;
    architecture.accept(&visitor);
    
    ast::compo::CProvision provision;
    provision.accept(&visitor);
    
    ast::compo::CRequirement requirement;
    requirement.accept(&visitor);
    
    ast::compo::CService service;
    service.accept(&visitor);
    
    ast::compo::CConstraint constraint;
    constraint.accept(&visitor);
    
    ast::compo::CConnection connection;
    connection.accept(&visitor);
    
    ast::compo::CDisconnection disconnection;
    disconnection.accept(&visitor);
    
    BOOST_CHECK_EQUAL(" CDescriptor CArchitecture CProvision CRequirement CService CConstraint CConnection CDisconnection", visitor.getNodes());
}

BOOST_AUTO_TEST_SUITE_END()