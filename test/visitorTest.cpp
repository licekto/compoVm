#include <iostream>
#include <memory>

#include <boost/test/unit_test.hpp>

#include "testDefinitions.h"

#include "definitions.h"

BOOST_AUTO_TEST_SUITE(visitorTest)

class testVisitor : public ast::visitors::CAbstractVisitor {
    
    private:
        std::string nodes;
    
    public:
        
        virtual void visit(ast::CNode */* node */) {nodes += " CNode";}
        virtual void visit(ast::CProgram */* node */) {nodes += " CProgram";};

        virtual void visit(ast::compo::CAbstractReqProv */* node */) {nodes += " CAbstractReqProv";}
        virtual void visit(ast::compo::CAbstractServConstr */* node */) {nodes += " CAbstractServConstr";}
        virtual void visit(ast_architecture */* node */) {nodes += " CArchitecture";}
        virtual void visit(ast::compo::CBind */* node */) {nodes += " CBind";}
        virtual void visit(ast_collectionportliteral */* node */) {nodes += " CCollectionPortLiteral";}
        virtual void visit(ast_connection */* node */) {nodes += " CConnection";}
        virtual void visit(ast_constraint */* node */) {nodes += " CConstraint";}
        virtual void visit(ast_delegation */* node */) {nodes += " CDelegation";}
        virtual void visit(ast_dereference */* node */) {nodes += " CDereferenceLiteral";}
        virtual void visit(ast_descriptor */* node */) {nodes += " CDescriptor";}
        virtual void visit(ast_disconnection */* node */) {nodes += " CDisconnection";}
        virtual void visit(ast_injectedport */* node */) {nodes += " CInjectedPort";}
        virtual void visit(ast_interface */* node */) {nodes += " CInterface";}
        virtual void visit(ast_namedport */* node */) {nodes += " CNamedPort";}
        virtual void visit(ast::compo::CPort */* node */) {nodes += " CPort";}
        virtual void visit(ast_portaddress */* node */) {nodes += " CPortAddress";}
        virtual void visit(ast_provision */* node */) {nodes += " CProvision";}
        virtual void visit(ast_requirement */* node */) {nodes += " CRequirement";}
        virtual void visit(ast_service */* node */) {nodes += " CService";}
        virtual void visit(ast_serviceinvocation */* node */) {nodes += " CServiceInvocation";}
        virtual void visit(ast_servicesignature */* node */) {nodes += " CServiceSignature";}
        virtual void visit(ast_signaturesport */* node */) {nodes += " CSignaturesPort";}
        virtual void visit(ast_universalport */* node */) {nodes += " CUniversalPort";}

        virtual void visit(ast::procedural::CAbstractExpression */* node */) {nodes += " CAbstractExpression";}
        virtual void visit(ast::procedural::CAbstractPrimaryExpression */* node */) {nodes += " CAbstractPrimaryExpression";}
        virtual void visit(ast::procedural::CAbstractStatement */* node */) {nodes += " CAbstractStatement";}
        virtual void visit(ast_addition * /* node */) {nodes += " CAdditionExpression";}
        virtual void visit(ast_assignment */* node */) {nodes += " CAssignmentExpression";}
        virtual void visit(ast::procedural::CBinaryExpression */* node */) {nodes += " CBinaryExpression";}
        virtual void visit(ast_break */* node */) {nodes += " CBreakStatement";}
        virtual void visit(ast_compound */* node */) {nodes += " CCompoundBody";}
        virtual void visit(ast_constant */* node */) {nodes += " CConstant";}
        virtual void visit(ast_continue */* node */) {nodes += " CContinueStatement";}
        virtual void visit(ast_division * /* node */) {nodes += " CDivisionExpression";}
        virtual void visit(ast_equality * /* node */) {nodes += " CEqualityExpression";}
        virtual void visit(ast_for */* node */) {nodes += " CForStatement";}
        virtual void visit(ast_greater * /* node */) {nodes += " CGreaterExpression";}
        virtual void visit(ast_greaterorequal * /* node */) {nodes += " CGreaterOrEqualExpression";}
        virtual void visit(ast_if */* node */) {nodes += " CIfStatement";}
        virtual void visit(ast_less * /* node */) {nodes += " CLessExpression";}
        virtual void visit(ast_lessorequal * /* node */) {nodes += " CLessOrEqualExpression";}
        virtual void visit(ast_and * /* node */) {nodes += " CLogicalAndExpression";}
        virtual void visit(ast_or * /* node */) {nodes += " CLogicalOrExpression";}
        virtual void visit(ast_multiplication * /* node */) {nodes += " CMultiplicationExpression";}
        virtual void visit(ast_nonequality * /* node */) {nodes += " CNonEqualityExpression";}
        virtual void visit(ast_parens */* node */) {nodes += " CParens";}
        virtual void visit(ast_return */* node */) {nodes += " CReturnStatement";}
        virtual void visit(ast_subtraction * /* node */) {nodes += " CSubtractionExpression";}
        virtual void visit(ast_string */* node */) {nodes += " CStringLiteral";}
        virtual void visit(ast_symbol */* node */) {nodes += " CSymbol";}
        virtual void visit(ast_while */* node */) {nodes += " CWhileStatement";}
        
        std::string getNodes() const {
            return nodes;
        }
};

BOOST_AUTO_TEST_CASE(basic) {
    
    testVisitor visitor;
    
    ast_descriptor descriptor;
    descriptor.accept(&visitor);
    
    ast_architecture architecture;
    architecture.accept(&visitor);
    
    ast_provision provision;
    provision.accept(&visitor);
    
    ast_requirement requirement;
    requirement.accept(&visitor);
    
    ast_service service;
    service.accept(&visitor);
    
    ast_constraint constraint;
    constraint.accept(&visitor);
    
    ast_connection connection;
    connection.accept(&visitor);
    
    ast_disconnection disconnection;
    disconnection.accept(&visitor);
    
    BOOST_CHECK_EQUAL(" CDescriptor CArchitecture CProvision CRequirement CService CConstraint CConnection CDisconnection", visitor.getNodes());
}

BOOST_AUTO_TEST_SUITE_END()
