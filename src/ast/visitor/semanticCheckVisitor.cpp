#include "ast/visitor/semanticCheckVisitor.h"

namespace ast {

	namespace visitors {

		void CSemanticCheckVisitor::checkDescriptorArchitecture(std::shared_ptr<ast::nodes::compo::CDescriptor> node) {

			if (m_descriptorTable.symbolFound(node->getNameSymbol()->getStringValue())) {
				throw exceptions::semantic::CRedefinitionDescriptorException(node->getNameSymbol()->getStringValue());
			}
			m_descriptorTable.addSymbol(node);

			if (!m_descriptorTable.symbolFound(node->getExtendsSymbol()->getStringValue())) {
				throw exceptions::semantic::CUndefinedDescriptorException(node->getExtendsSymbol()->getStringValue());
			}
		}

		void CSemanticCheckVisitor::checkNodeType(std::shared_ptr<ast::nodes::CNode> node, ast_type type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}

		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::CNode> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CAbstractReqProv> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CAbstractServConstr> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CBind> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CPort> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CAbstractExpression> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CAbstractPrimaryExpression> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CAbstractStatement> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CBinaryExpression> node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::CProgram> node) {
			checkNodeType(node, ast_type::PROGRAM);

			if (node->getNodesSize() == 0) {
				//throw exceptions::semantic::CEmptyProgramException;
			}

			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CArchitecture> node) {
			checkNodeType(node, ast_type::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CCollectionPortLiteral> node) {
			checkNodeType(node, ast_type::COLLECTION_PORT);

			node->getPortName()->accept(shared_from_this());
			node->getIndexExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CConnection> node) {
			checkNodeType(node, ast_type::CONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CConstraint> node) {
			checkNodeType(node, ast_type::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CDelegation> node) {
			checkNodeType(node, ast_type::DELEGATION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CDereferenceLiteral> node) {
			checkNodeType(node, ast_type::DEREFERENCE);

			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CDescriptor> node) {
			checkNodeType(node, ast_type::DESCRIPTOR);

			node->getNameSymbol()->accept(shared_from_this());

			node->getInProvision()->accept(shared_from_this());
			node->getExProvision()->accept(shared_from_this());
			node->getInRequirement()->accept(shared_from_this());
			node->getExRequirement()->accept(shared_from_this());
			node->getArchitecture()->accept(shared_from_this());

			for (size_t i = 0; i < node->getServicesSize(); ++i) {
				node->getServiceAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getConstraintsSize(); ++i) {
				node->getConstraintAt(i)->accept(shared_from_this());
			}

			checkDescriptorArchitecture(node);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CDisconnection> node) {
			checkNodeType(node, ast_type::DISCONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CInjectedPort> node) {
			checkNodeType(node, ast_type::INJECTED_PORT);

			node->getInjectedWith()->accept(shared_from_this());
			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CInterface> node) {
			checkNodeType(node, ast_type::INTERFACE);

			node->getExtendsSymbol()->accept(shared_from_this());
			node->getNameSymbol()->accept(shared_from_this());

			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CNamedPort> node) {
			checkNodeType(node, ast_type::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CPortAddress> node) {
			checkNodeType(node, ast_type::PORT_ADDRESS);

			node->getComponent()->accept(shared_from_this());
			node->getPortName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CProvision> node) {
			checkNodeType(node, ast_type::PROVISION);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CRequirement> node) {
			checkNodeType(node, ast_type::REQUIREMENT);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CService> node) {
			checkNodeType(node, ast_type::SERVICE);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CServiceInvocation> node) {
			checkNodeType(node, ast_type::SERVICE_INVOCATION);

			node->getParameters()->accept(shared_from_this());
			node->getReceiverName()->accept(shared_from_this());
			node->getSelectorName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CServiceSignature> node) {
			checkNodeType(node, ast_type::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CSignaturesPort> node) {
			checkNodeType(node, ast_type::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::compo::CUniversalPort> node) {
			checkNodeType(node, ast_type::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CAdditionExpression> node) {
			checkNodeType(node, ast_type::ADDITION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CAssignmentExpression> node) {
			checkNodeType(node, ast_type::ASSIGNMENT_EXPRESSION);

			node->getRValue()->accept(shared_from_this());
			node->getVariable()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CBreakStatement> node) {
			checkNodeType(node, ast_type::BREAK);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CCompoundBody> node) {
			checkNodeType(node, ast_type::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CConstant> node) {
			checkNodeType(node, ast_type::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CContinueStatement> node) {
			checkNodeType(node, ast_type::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CDivisionExpression> node) {
			checkNodeType(node, ast_type::DIVISION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CEqualityExpression> node) {
			checkNodeType(node, ast_type::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CForStatement> node) {
			checkNodeType(node, ast_type::FOR);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
			node->getIncrement()->accept(shared_from_this());
			node->getInitExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CGreaterExpression> node) {
			checkNodeType(node, ast_type::GREATER_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CGreaterOrEqualExpression> node) {
			checkNodeType(node, ast_type::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CIfStatement> node) {
			checkNodeType(node, ast_type::IF);

			node->getCondition()->accept(shared_from_this());
			node->getIfBody()->accept(shared_from_this());
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CLessExpression> node) {
			checkNodeType(node, ast_type::LESS_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CLessOrEqualExpression> node) {
			checkNodeType(node, ast_type::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CLogicalAndExpression> node) {
			checkNodeType(node, ast_type::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CLogicalOrExpression> node) {
			checkNodeType(node, ast_type::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CMultiplicationExpression> node) {
			checkNodeType(node, ast_type::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CNonEqualityExpression> node) {
			checkNodeType(node, ast_type::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CParens> node) {
			checkNodeType(node, ast_type::PARENS);

			node->getExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CReturnStatement> node) {
			checkNodeType(node, ast_type::RETURN);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CSubtractionExpression> node) {
			checkNodeType(node, ast_type::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CStringLiteral> node) {
			checkNodeType(node, ast_type::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CSymbol> node) {
			checkNodeType(node, ast_type::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(std::shared_ptr<ast::nodes::procedural::CWhileStatement> node) {
			checkNodeType(node, ast_type::WHILE);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
		}
	}

}
