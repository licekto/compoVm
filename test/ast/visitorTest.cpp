#include <iostream>
#include <memory>
#include <string>

#include <boost/test/unit_test.hpp>

#include "ast/visitor/abstractVisitor.h"
#include "testDefinitions.h"
#include "definitions/allDefinitions.h"

BOOST_AUTO_TEST_SUITE(visitorTest)

class testVisitor : public ast::visitors::CAbstractVisitor, public std::enable_shared_from_this<testVisitor> {
    
    private:
        std::string nodes;
    
    public:
        
        virtual void visit(ptr(ast_node)  /* node */) {nodes += " CNode";}
        virtual void visit(ptr(ast_program)  /* node */) {nodes += " CProgram";}

        virtual void visit(ptr(ast_reqprov)  /* node */) {nodes += " CAbstractReqProv";}
        virtual void visit(ptr(ast_architecture)  /* node */) {nodes += " CArchitecture";}
        virtual void visit(ptr(ast_bind)  /* node */) {nodes += " CBind";}
        virtual void visit(ptr(ast_collectionportliteral)  /* node */) {nodes += " CCollectionPortLiteral";}
        virtual void visit(ptr(ast_connection)  /* node */) {nodes += " CConnection";}
        virtual void visit(ptr(ast_constraint)  /* node */) {nodes += " CConstraint";}
        virtual void visit(ptr(ast_delegation)  /* node */) {nodes += " CDelegation";}
        virtual void visit(ptr(ast_dereference)  /* node */) {nodes += " CDereferenceLiteral";}
        virtual void visit(ptr(ast_descriptor)  /* node */) {nodes += " CDescriptor";}
        virtual void visit(ptr(ast_disconnection)  /* node */) {nodes += " CDisconnection";}
        virtual void visit(ptr(ast_injectedport)  /* node */) {nodes += " CInjectedPort";}
        virtual void visit(ptr(ast_interface)  /* node */) {nodes += " CInterface";}
        virtual void visit(ptr(ast_namedport)  /* node */) {nodes += " CNamedPort";}
        virtual void visit(ptr(ast_port)  /* node */) {nodes += " CPort";}
        virtual void visit(ptr(ast_portaddress)  /* node */) {nodes += " CPortAddress";}
        virtual void visit(ptr(ast_provision)  /* node */) {nodes += " CProvision";}
        virtual void visit(ptr(ast_requirement)  /* node */) {nodes += " CRequirement";}
        virtual void visit(ptr(ast_service)  /* node */) {nodes += " CService";}
        virtual void visit(ptr(ast_serviceinvocation)  /* node */) {nodes += " CServiceInvocation";}
        virtual void visit(ptr(ast_servicesignature)  /* node */) {nodes += " CServiceSignature";}
        virtual void visit(ptr(ast_signaturesport)  /* node */) {nodes += " CSignaturesPort";}
        virtual void visit(ptr(ast_universalport)  /* node */) {nodes += " CUniversalPort";}

        virtual void visit(ptr(ast_expression)  /* node */) {nodes += " CAbstractExpression";}
        virtual void visit(ptr(ast_primaryexpression)  /* node */) {nodes += " CAbstractPrimaryExpression";}
        virtual void visit(ptr(ast_statement)  /* node */) {nodes += " CAbstractStatement";}
        virtual void visit(ptr(ast_addition)  /* node */) {nodes += " CAdditionExpression";}
        virtual void visit(ptr(ast_assignment)  /* node */) {nodes += " CAssignmentExpression";}
        virtual void visit(ptr(ast_binary)  /* node */) {nodes += " CBinaryExpression";}
        virtual void visit(ptr(ast_break)  /* node */) {nodes += " CBreakStatement";}
        virtual void visit(ptr(ast_compound)  /* node */) {nodes += " CCompoundBody";}
        virtual void visit(ptr(ast_constant)  /* node */) {nodes += " CConstant";}
        virtual void visit(ptr(ast_continue)  /* node */) {nodes += " CContinueStatement";}
        virtual void visit(ptr(ast_division)  /* node */) {nodes += " CDivisionExpression";}
        virtual void visit(ptr(ast_equality)  /* node */) {nodes += " CEqualityExpression";}
        virtual void visit(ptr(ast_for)  /* node */) {nodes += " CForStatement";}
        virtual void visit(ptr(ast_greater)  /* node */) {nodes += " CGreaterExpression";}
        virtual void visit(ptr(ast_greaterorequal)  /* node */) {nodes += " CGreaterOrEqualExpression";}
        virtual void visit(ptr(ast_if)  /* node */) {nodes += " CIfStatement";}
        virtual void visit(ptr(ast_less)  /* node */) {nodes += " CLessExpression";}
        virtual void visit(ptr(ast_lessorequal)  /* node */) {nodes += " CLessOrEqualExpression";}
        virtual void visit(ptr(ast_and)  /* node */) {nodes += " CLogicalAndExpression";}
        virtual void visit(ptr(ast_or)  /* node */) {nodes += " CLogicalOrExpression";}
        virtual void visit(ptr(ast_multiplication)  /* node */) {nodes += " CMultiplicationExpression";}
        virtual void visit(ptr(ast_nonequality)  /* node */) {nodes += " CNonEqualityExpression";}
        virtual void visit(ptr(ast_parens)  /* node */) {nodes += " CParens";}
        virtual void visit(ptr(ast_return)  /* node */) {nodes += " CReturnStatement";}
        virtual void visit(ptr(ast_subtraction)  /* node */) {nodes += " CSubtractionExpression";}
        virtual void visit(ptr(ast_string)  /* node */) {nodes += " CStringLiteral";}
        virtual void visit(ptr(ast_symbol)  /* node */) {nodes += " CSymbol";}
        virtual void visit(ptr(ast_while)  /* node */) {nodes += " CWhileStatement";}
        
        std::string getNodes() const {
            return nodes;
        }
};

BOOST_AUTO_TEST_CASE(basic) {
    
    std::shared_ptr<testVisitor> visitor = std::make_shared<testVisitor>();
    
    ptr(ast_descriptor) descriptor = new_ptr(ast_descriptor)();
    descriptor->accept(visitor);
    
    ptr(ast_architecture) architecture = new_ptr(ast_architecture)();
    architecture->accept(visitor);
    
    ptr(ast_provision) provision = new_ptr(ast_provision)();
    provision->accept(visitor);
    
    ptr(ast_requirement) requirement = new_ptr(ast_requirement)();
    requirement->accept(visitor);
    
    ptr(ast_service) service = new_ptr(ast_service)();
    service->accept(visitor);
    
    ptr(ast_constraint) constraint = new_ptr(ast_constraint)();
    constraint->accept(visitor);
    
    ptr(ast_connection) connection = new_ptr(ast_connection)();
    connection->accept(visitor);
    
    ptr(ast_disconnection) disconnection = new_ptr(ast_disconnection)();
    disconnection->accept(visitor);
    
    BOOST_CHECK_EQUAL(" CDescriptor CArchitecture CProvision CRequirement CService CConstraint CConnection CDisconnection", visitor->getNodes());
}

BOOST_AUTO_TEST_SUITE_END()
