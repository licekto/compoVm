#include "ast/visitor/semanticCheckVisitor.h"
#include "exceptions/semantic/emptyProgramException.h"
#include "ast/semantic/globalDescriptorsTable.h"

namespace ast {

	namespace visitors {

                void CSemanticCheckVisitor::checkDescriptorArchitecture(ast::nodes::compo::CDescriptor *node) {
                    
                }
            
		void CSemanticCheckVisitor::checkNodeType(ast::nodes::CNode *node, ast_type type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}
                
		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(ast::nodes::CNode *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::compo::CAbstractReqProv *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::compo::CAbstractServConstr *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::compo::CBind *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::compo::CPort *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CAbstractExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CAbstractPrimaryExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CAbstractStatement *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CBinaryExpression *node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(ast::nodes::CProgram *node) {
			checkNodeType(node, ast_type::PROGRAM);

                        if (node->getNodesSize() == 0) {
                            //throw exceptions::semantic::CEmptyProgramException;
                        }
                        
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CArchitecture *node) {
			checkNodeType(node, ast_type::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CCollectionPortLiteral *node) {
			checkNodeType(node, ast_type::COLLECTION_PORT);

			node->getPortName()->accept(this);
			node->getIndexExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CConnection *node) {
			checkNodeType(node, ast_type::CONNECTION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CConstraint *node) {
			checkNodeType(node, ast_type::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CDelegation *node) {
			checkNodeType(node, ast_type::DELEGATION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CDereferenceLiteral *node) {
			checkNodeType(node, ast_type::DEREFERENCE);

			node->getParamName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CDescriptor *node) {
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
                        
                        //m_descriptorTable.addSymbol(node);
                        
                        checkDescriptorArchitecture(node);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CDisconnection *node) {
			checkNodeType(node, ast_type::DISCONNECTION);

			node->getPortIdentification1()->accept(this);
			node->getPortIdentification2()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CInjectedPort *node) {
			checkNodeType(node, ast_type::INJECTED_PORT);

			node->getInjectedWith()->accept(this);
			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CInterface *node) {
			checkNodeType(node, ast_type::INTERFACE);

			node->getExtendsSymbol()->accept(this);
			node->getNameSymbol()->accept(this);

			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CNamedPort *node) {
			checkNodeType(node, ast_type::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
			node->getParamName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CPortAddress *node) {
			checkNodeType(node, ast_type::PORT_ADDRESS);

			node->getComponent()->accept(this);
			node->getPortName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CProvision *node) {
			checkNodeType(node, ast_type::PROVISION);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CRequirement *node) {
			checkNodeType(node, ast_type::REQUIREMENT);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CService *node) {
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

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CServiceInvocation *node) {
			checkNodeType(node, ast_type::SERVICE_INVOCATION);

			node->getParameters()->accept(this);
			node->getReceiverName()->accept(this);
			node->getSelectorName()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CServiceSignature *node) {
			checkNodeType(node, ast_type::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(this);
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CSignaturesPort *node) {
			checkNodeType(node, ast_type::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::compo::CUniversalPort *node) {
			checkNodeType(node, ast_type::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(this);
			}
			node->getNameSymbol()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CAdditionExpression *node) {
			checkNodeType(node, ast_type::ADDITION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CAssignmentExpression *node) {
			checkNodeType(node, ast_type::ASSIGNMENT_EXPRESSION);

			node->getRValue()->accept(this);
			node->getVariable()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CBreakStatement *node) {
			checkNodeType(node, ast_type::BREAK);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CCompoundBody *node) {
			checkNodeType(node, ast_type::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this);
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CConstant *node) {
			checkNodeType(node, ast_type::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CContinueStatement *node) {
			checkNodeType(node, ast_type::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CDivisionExpression *node) {
			checkNodeType(node, ast_type::DIVISION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CEqualityExpression *node) {
			checkNodeType(node, ast_type::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CForStatement *node) {
			checkNodeType(node, ast_type::FOR);

			node->getBody()->accept(this);
			node->getCondition()->accept(this);
			node->getIncrement()->accept(this);
			node->getInitExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CGreaterExpression *node) {
			checkNodeType(node, ast_type::GREATER_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CGreaterOrEqualExpression *node) {
			checkNodeType(node, ast_type::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CIfStatement *node) {
			checkNodeType(node, ast_type::IF);

			node->getCondition()->accept(this);
			node->getIfBody()->accept(this);
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(this);
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CLessExpression *node) {
			checkNodeType(node, ast_type::LESS_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CLessOrEqualExpression *node) {
			checkNodeType(node, ast_type::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CLogicalAndExpression *node) {
			checkNodeType(node, ast_type::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CLogicalOrExpression *node) {
			checkNodeType(node, ast_type::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CMultiplicationExpression *node) {
			checkNodeType(node, ast_type::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CNonEqualityExpression *node) {
			checkNodeType(node, ast_type::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CParens *node) {
			checkNodeType(node, ast_type::PARENS);

			node->getExpression()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CReturnStatement *node) {
			checkNodeType(node, ast_type::RETURN);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CSubtractionExpression *node) {
			checkNodeType(node, ast_type::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(this);
			node->getOperand1()->accept(this);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CStringLiteral *node) {
			checkNodeType(node, ast_type::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CSymbol *node) {
			checkNodeType(node, ast_type::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(ast::nodes::procedural::CWhileStatement *node) {
			checkNodeType(node, ast_type::WHILE);

			node->getBody()->accept(this);
			node->getCondition()->accept(this);
		}
	}

}
