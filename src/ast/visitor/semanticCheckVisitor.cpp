#include "ast/visitor/semanticCheckVisitor.h"
#include "exceptions/semantic/emptyProgramException.h"

namespace ast {

	namespace visitors {

                void CSemanticCheckVisitor::checkDescriptorArchitecture(ast::compo::CDescriptor *node) {
                    
                }
            
		void CSemanticCheckVisitor::checkNodeType(ast::CNode *node, ast_type type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}
                
		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(ast::CNode *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::compo::CAbstractReqProv *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::compo::CAbstractServConstr *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::compo::CBind *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::compo::CPort *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::procedural::CAbstractExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::procedural::CAbstractPrimaryExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::procedural::CAbstractStatement *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::procedural::CBinaryExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(ast::CProgram *node) {
			checkNodeType(node, ast_type::PROGRAM);

                        if (node->getNodesSize() == 0) {
                            //throw exceptions::semantic::CEmptyProgramException;
                        }
                        
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CArchitecture *node) {
			checkNodeType(node, ast_type::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CCollectionPortLiteral *node) {
			checkNodeType(node, ast_type::COLLECTION_PORT);

			node->getPortName()->accept(this);
			node->getIndexExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CConnection *node) {
			checkNodeType(node, ast_type::CONNECTION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CConstraint *node) {
			checkNodeType(node, ast_type::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CDelegation *node) {
			checkNodeType(node, ast_type::DELEGATION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CDereferenceLiteral *node) {
			checkNodeType(node, ast_type::DEREFERENCE);

			node->getParamName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CDescriptor *node) {
			checkNodeType(node, ast_type::DESCRIPTOR);

			node->getNameSymbol()->accept(this);

			node->getInProvision()->accept(this);
			node->getExProvision()->accept(this);
			node->getInRequirement()->accept(this);
			node->getExRequirement()->accept(this);
			node->getArchitecture()->accept(this);

			for (size_t i = 0; i < node->getServicesSize(); ++i) {
				node->getServiceAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getConstraintsSize(); ++i) {
				node->getConstraintAt(i)->accept(this);
			}
                        
                        checkDescriptorArchitecture(node);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CDisconnection *node) {
			checkNodeType(node, ast_type::DISCONNECTION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CInjectedPort *node) {
			checkNodeType(node, ast_type::INJECTED_PORT);

			node->getInjectedWith()->accept(this);
			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CInterface *node) {
			checkNodeType(node, ast_type::INTERFACE);

			node->getExtendsSymbol()->accept(this);
			node->getNameSymbol()->accept(this);

			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CNamedPort *node) {
			checkNodeType(node, ast_type::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
			node->getParamName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CPortAddress *node) {
			checkNodeType(node, ast_type::PORT_ADDRESS);

			node->getComponent()->accept(this);
			node->getPortName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CProvision *node) {
			checkNodeType(node, ast_type::PROVISION);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CRequirement *node) {
			checkNodeType(node, ast_type::REQUIREMENT);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CService *node) {
			checkNodeType(node, ast_type::SERVICE);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CServiceInvocation *node) {
			checkNodeType(node, ast_type::SERVICE_INVOCATION);

			node->getParameters()->accept(this);
			node->getReceiverName()->accept(this);
			node->getSelectorName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::compo::CServiceSignature *node) {
			checkNodeType(node, ast_type::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(this);
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CSignaturesPort *node) {
			checkNodeType(node, ast_type::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::compo::CUniversalPort *node) {
			checkNodeType(node, ast_type::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CAdditionExpression *node) {
			checkNodeType(node, ast_type::ADDITION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CAssignmentExpression *node) {
			checkNodeType(node, ast_type::ASSIGNMENT_EXPRESSION);

			node->getRValue()->accept(this);
			node->getVariable()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CBreakStatement *node) {
			checkNodeType(node, ast_type::BREAK);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CCompoundBody *node) {
			checkNodeType(node, ast_type::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CConstant *node) {
			checkNodeType(node, ast_type::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CContinueStatement *node) {
			checkNodeType(node, ast_type::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CDivisionExpression *node) {
			checkNodeType(node, ast_type::DIVISION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CEqualityExpression *node) {
			checkNodeType(node, ast_type::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CForStatement *node) {
			checkNodeType(node, ast_type::FOR);

			node->getBody()->accept(this);
			node->getCondition()->accept(this);
			node->getIncrement()->accept(this);
			node->getInitExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CGreaterExpression *node) {
			checkNodeType(node, ast_type::GREATER_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CGreaterOrEqualExpression *node) {
			checkNodeType(node, ast_type::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CIfStatement *node) {
			checkNodeType(node, ast_type::IF);

			node->getCondition()->accept(this);
			node->getIfBody()->accept(this);
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CLessExpression *node) {
			checkNodeType(node, ast_type::LESS_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CLessOrEqualExpression *node) {
			checkNodeType(node, ast_type::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CLogicalAndExpression *node) {
			checkNodeType(node, ast_type::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CLogicalOrExpression *node) {
			checkNodeType(node, ast_type::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CMultiplicationExpression *node) {
			checkNodeType(node, ast_type::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CNonEqualityExpression *node) {
			checkNodeType(node, ast_type::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CParens *node) {
			checkNodeType(node, ast_type::PARENS);

			node->getExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CReturnStatement *node) {
			checkNodeType(node, ast_type::RETURN);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CSubtractionExpression *node) {
			checkNodeType(node, ast_type::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CStringLiteral *node) {
			checkNodeType(node, ast_type::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CSymbol *node) {
			checkNodeType(node, ast_type::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(ast::procedural::CWhileStatement *node) {
			checkNodeType(node, ast_type::WHILE);

			node->getBody()->accept(this);
			node->getCondition()->accept(this);
		}
	}

}
