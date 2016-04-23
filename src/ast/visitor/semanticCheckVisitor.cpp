#include "ast/visitor/semanticCheckVisitor.h"

namespace ast {

	namespace visitors {

		CSemanticCheckVisitor::CSemanticCheckVisitor(ptr(ast::semantic::CSyntaxDescriptorTable) descriptorTable)
			: m_descriptorTable(descriptorTable), m_currentDescriptor(nullptr) {

		}

		void CSemanticCheckVisitor::checkDescriptorInterface(ptr(ast_descriptorinterface) node) {
			if (m_descriptorTable.use_count()) {
				if (!m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
					if (node->getNodeType() == type_node::DESCRIPTOR) {
						throw exceptions::semantic::CUndefinedDescriptorException(node->getNameSymbol()->getStringValue());
					} else if (node->getNodeType() == type_node::INTERFACE) {
						throw exceptions::semantic::CUndefinedInterfaceException(node->getNameSymbol()->getStringValue());
					}
				}

				if (node->getExtendsSymbol().use_count()) {
					if (!m_descriptorTable->symbolFound(node->getExtendsSymbol()->getStringValue())) {
						if (node->getNodeType() == type_node::DESCRIPTOR) {
							throw exceptions::semantic::CUndefinedDescriptorException(node->getExtendsSymbol()->getStringValue());
						} else if (node->getNodeType() == type_node::INTERFACE) {
							throw exceptions::semantic::CUndefinedInterfaceException(node->getExtendsSymbol()->getStringValue());
						}
					}
					type_node t = m_descriptorTable->getSymbol(node->getExtendsSymbol()->getStringValue())->getNodeType();
					if (t != node->getNodeType()) {
						throw exceptions::semantic::CWrongBaseTypeException(t, node->getNodeType());
					}
				}
			}
		}

		void CSemanticCheckVisitor::checkNodeType(ptr(ast_node) node, type_node type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}

		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(ptr(ast_node) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_bind) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_port) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_expression) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_primaryexpression) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_statement) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_binary) node) {
			checkNodeType(node, type_node::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(ptr(ast_program) node) {
			checkNodeType(node, type_node::PROGRAM);



			if (node->getNodesSize() == 0) {
				throw exceptions::semantic::CEmptyProgramException();
			}

			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_architecture) node) {
			checkNodeType(node, type_node::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_collectionportliteral) node) {
			checkNodeType(node, type_node::COLLECTION_PORT);

			node->getPortName()->accept(shared_from_this());
			node->getIndexExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_connection) node) {
			checkNodeType(node, type_node::CONNECTION);

			node->getSourcePortIdentification()->accept(shared_from_this());
			node->getDestinationPortIdentification()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_constraint) node) {
			checkNodeType(node, type_node::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_delegation) node) {
			checkNodeType(node, type_node::DELEGATION);

			node->getSourcePortIdentification()->accept(shared_from_this());
			node->getDestinationPortIdentification()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_dereference) node) {
			checkNodeType(node, type_node::DEREFERENCE);

			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_descriptor) node) {
			checkNodeType(node, type_node::DESCRIPTOR);

			node->getNameSymbol()->accept(shared_from_this());

			m_currentDescriptor = node;

			if (node->getArchitecture().use_count()) {
				node->getArchitecture()->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getServicesSize(); ++i) {
				node->getServiceAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getConstraintsSize(); ++i) {
				node->getConstraintAt(i)->accept(shared_from_this());
			}

			checkDescriptorInterface(node);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_disconnection) node) {
			checkNodeType(node, type_node::DISCONNECTION);

			node->getSourcePortIdentification()->accept(shared_from_this());
			node->getDestinationPortIdentification()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_injectedport) node) {

			throw exceptions::semantic::CUnsupportedFeatureException("Injected port");

			checkNodeType(node, type_node::INJECTED_PORT);

			node->getInjectedWith()->accept(shared_from_this());
			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_interface) node) {
			checkNodeType(node, type_node::INTERFACE);

			if (node->getExtendsSymbol().use_count()) {
				node->getExtendsSymbol()->accept(shared_from_this());
			}

			if (node->getNameSymbol().use_count()) {
				node->getNameSymbol()->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}

			checkDescriptorInterface(node);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_namedport) node) {
			checkNodeType(node, type_node::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			node->getComponentName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_portaddress) node) {
			checkNodeType(node, type_node::PORT_ADDRESS);

			node->getPortName()->accept(shared_from_this());
			node->getComponent()->accept(shared_from_this());

			// Direct component identifier
			if (node->getComponent()->getNodeType() == type_node::SYMBOL) {

			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_service) node) {
			checkNodeType(node, type_node::SERVICE);

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

		void CSemanticCheckVisitor::visit(ptr(ast_serviceinvocation) node) {
			checkNodeType(node, type_node::SERVICE_INVOCATION);

			node->getParameters()->accept(shared_from_this());
			node->getReceiverName()->accept(shared_from_this());
			node->getSelectorName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_servicesignature) node) {
			checkNodeType(node, type_node::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_signaturesport) node) {
			checkNodeType(node, type_node::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

                void CSemanticCheckVisitor::visit(ptr(ast_sizeof) node) {
			checkNodeType(node, type_node::SIZEOF);
                        node->getParamName()->accept(shared_from_this());
		}
                
		void CSemanticCheckVisitor::visit(ptr(ast_universalport) node) {
			checkNodeType(node, type_node::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_addition) node) {
			checkNodeType(node, type_node::ADDITION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_assignment) node) {
			checkNodeType(node, type_node::ASSIGNMENT_EXPRESSION);

			node->getRightSide()->accept(shared_from_this());
			node->getVariable()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_break) node) {
			checkNodeType(node, type_node::BREAK);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_compound) node) {
			checkNodeType(node, type_node::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_constant) node) {
			checkNodeType(node, type_node::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_boolean) node) {
			checkNodeType(node, type_node::BOOLEAN);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_continue) node) {
			checkNodeType(node, type_node::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_division) node) {
			checkNodeType(node, type_node::DIVISION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_equality) node) {
			checkNodeType(node, type_node::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_for) node) {
			checkNodeType(node, type_node::FOR);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
			node->getIncrement()->accept(shared_from_this());
			node->getInitExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greater) node) {
			checkNodeType(node, type_node::GREATER_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greaterorequal) node) {
			checkNodeType(node, type_node::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_if) node) {
			checkNodeType(node, type_node::IF);

			node->getCondition()->accept(shared_from_this());
			node->getIfBody()->accept(shared_from_this());
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_less) node) {
			checkNodeType(node, type_node::LESS_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_lessorequal) node) {
			checkNodeType(node, type_node::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_and) node) {
			checkNodeType(node, type_node::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_or) node) {
			checkNodeType(node, type_node::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_multiplication) node) {
			checkNodeType(node, type_node::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_nonequality) node) {
			checkNodeType(node, type_node::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_parens) node) {
			checkNodeType(node, type_node::PARENS);

			node->getExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_return) node) {
			checkNodeType(node, type_node::RETURN);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_subtraction) node) {
			checkNodeType(node, type_node::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_string) node) {
			checkNodeType(node, type_node::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_symbol) node) {
			checkNodeType(node, type_node::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_while) node) {
			checkNodeType(node, type_node::WHILE);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
		}
	}

}
