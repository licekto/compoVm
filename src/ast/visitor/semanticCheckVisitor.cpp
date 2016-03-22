#include "ast/visitor/semanticCheckVisitor.h"
#include "exceptions/semantic/wrongBaseTypeException.h"
#include "exceptions/semantic/undefinedPortException.h"
#include "exceptions/semantic/unsupportedFeatureException.h"
#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"

namespace ast {

	namespace visitors {

		CSemanticCheckVisitor::CSemanticCheckVisitor(ptr(ast::semantic::CGlobalDescriptorTable) descriptorTable)
			: m_descriptorTable(descriptorTable), m_currentDescriptor(nullptr) {

		}

		void CSemanticCheckVisitor::checkDescriptorInterface(ptr(ast_descriptorinterface) node) {
			if (m_descriptorTable.use_count()) {
				if (!m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
					if (node->getNodeType() == ast_nodetype::DESCRIPTOR) {
						throw exceptions::semantic::CUndefinedDescriptorException(node->getNameSymbol()->getStringValue());
					} else if (node->getNodeType() == ast_nodetype::INTERFACE) {
						throw exceptions::semantic::CUndefinedInterfaceException(node->getNameSymbol()->getStringValue());
					}
				}

				if (node->getExtendsSymbol().use_count()) {
					if (!m_descriptorTable->symbolFound(node->getExtendsSymbol()->getStringValue())) {
						if (node->getNodeType() == ast_nodetype::DESCRIPTOR) {
							throw exceptions::semantic::CUndefinedDescriptorException(node->getExtendsSymbol()->getStringValue());
						} else if (node->getNodeType() == ast_nodetype::INTERFACE) {
							throw exceptions::semantic::CUndefinedInterfaceException(node->getExtendsSymbol()->getStringValue());
						}
					}
					ast_nodetype t = m_descriptorTable->getSymbol(node->getExtendsSymbol()->getStringValue())->getNodeType();
					if (t != node->getNodeType()) {
						throw exceptions::semantic::CWrongBaseTypeException(t, node->getNodeType());
					}
				}
			}
		}

		void CSemanticCheckVisitor::checkNodeType(ptr(ast_node) node, ast_nodetype type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}

		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(ptr(ast_node) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_reqprov) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_servconstr) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_bind) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_port) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_expression) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_primaryexpression) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_statement) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_binary) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(ptr(ast_program) node) {
			checkNodeType(node, ast_nodetype::PROGRAM);

			if (node->getNodesSize() == 0) {
				throw exceptions::semantic::CEmptyProgramException();
			}

			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_architecture) node) {
			checkNodeType(node, ast_nodetype::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_collectionportliteral) node) {
			checkNodeType(node, ast_nodetype::COLLECTION_PORT);

			node->getPortName()->accept(shared_from_this());
			node->getIndexExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_connection) node) {
			checkNodeType(node, ast_nodetype::CONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());


		}

		void CSemanticCheckVisitor::visit(ptr(ast_constraint) node) {
			checkNodeType(node, ast_nodetype::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_delegation) node) {
			checkNodeType(node, ast_nodetype::DELEGATION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_dereference) node) {
			checkNodeType(node, ast_nodetype::DEREFERENCE);

			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_descriptor) node) {
			checkNodeType(node, ast_nodetype::DESCRIPTOR);

			node->getNameSymbol()->accept(shared_from_this());

			m_currentDescriptor = node;

			if (node->getInProvision().use_count()) {
				node->getInProvision()->accept(shared_from_this());
			}

			if (node->getExProvision().use_count()) {
				node->getExProvision()->accept(shared_from_this());
			}

			if (node->getInRequirement().use_count()) {
				node->getInRequirement()->accept(shared_from_this());
			}

			if (node->getExRequirement().use_count()) {
				node->getExRequirement()->accept(shared_from_this());
			}

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
			checkNodeType(node, ast_nodetype::DISCONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_injectedport) node) {

			throw exceptions::semantic::CUnsupportedFeatureException("Injected port");

			checkNodeType(node, ast_nodetype::INJECTED_PORT);

			node->getInjectedWith()->accept(shared_from_this());
			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_interface) node) {
			checkNodeType(node, ast_nodetype::INTERFACE);

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
			checkNodeType(node, ast_nodetype::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_portaddress) node) {
			checkNodeType(node, ast_nodetype::PORT_ADDRESS);

			node->getPortName()->accept(shared_from_this());
			node->getComponent()->accept(shared_from_this());

			// Direct component identifier
			if (node->getComponent()->getNodeType() == ast_nodetype::SYMBOL) {

			}

			if (!m_currentDescriptor->portFound(node->getPortName()->getStringValue())) {
				throw exceptions::semantic::CUndefinedPortException(node->getPortName()->getStringValue());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_provision) node) {
			checkNodeType(node, ast_nodetype::PROVISION);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				ptr(ast_port) port = node->getPortAt(i);
				port->accept(shared_from_this());

				ast_visibilitytype type = node->getVisibilityType();
				if ((type == ast_visibilitytype::INTERNAL && m_currentDescriptor->exProvidedPortFound(port->getNameSymbol()->getStringValue()))
				 || (type == ast_visibilitytype::EXTERNAL && m_currentDescriptor->inProvidedPortFound(port->getNameSymbol()->getStringValue()))) {
                                    throw exceptions::semantic::CBidirectionalPortNotSupportedException(port->getNameSymbol()->getStringValue());
				}
                                
                                if (m_currentDescriptor->exRequiredPortFound(port->getNameSymbol()->getStringValue())
                                 || m_currentDescriptor->inRequiredPortFound(port->getNameSymbol()->getStringValue())) {
                                    throw exceptions::semantic::CBidirectionalPortNotSupportedException(port->getNameSymbol()->getStringValue());
				}
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_requirement) node) {
			checkNodeType(node, ast_nodetype::REQUIREMENT);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				ptr(ast_port) port = node->getPortAt(i);
				port->accept(shared_from_this());

				ast_visibilitytype type = node->getVisibilityType();
				if ((type == ast_visibilitytype::INTERNAL && m_currentDescriptor->exRequiredPortFound(port->getNameSymbol()->getStringValue()))
				 || (type == ast_visibilitytype::EXTERNAL && m_currentDescriptor->inRequiredPortFound(port->getNameSymbol()->getStringValue()))) {
                                    throw exceptions::semantic::CBidirectionalPortNotSupportedException(port->getNameSymbol()->getStringValue());
				}
                                
                                if (m_currentDescriptor->exProvidedPortFound(port->getNameSymbol()->getStringValue())
                                 || m_currentDescriptor->inProvidedPortFound(port->getNameSymbol()->getStringValue())) {
                                    throw exceptions::semantic::CBidirectionalPortNotSupportedException(port->getNameSymbol()->getStringValue());
				}
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_service) node) {
			checkNodeType(node, ast_nodetype::SERVICE);

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
			checkNodeType(node, ast_nodetype::SERVICE_INVOCATION);

			node->getParameters()->accept(shared_from_this());
			node->getReceiverName()->accept(shared_from_this());
			node->getSelectorName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_servicesignature) node) {
			checkNodeType(node, ast_nodetype::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_signaturesport) node) {
			checkNodeType(node, ast_nodetype::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_universalport) node) {
			checkNodeType(node, ast_nodetype::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_addition) node) {
			checkNodeType(node, ast_nodetype::ADDITION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_assignment) node) {
			checkNodeType(node, ast_nodetype::ASSIGNMENT_EXPRESSION);

			node->getRValue()->accept(shared_from_this());
			node->getVariable()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_break) node) {
			checkNodeType(node, ast_nodetype::BREAK);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_compound) node) {
			checkNodeType(node, ast_nodetype::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_constant) node) {
			checkNodeType(node, ast_nodetype::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_continue) node) {
			checkNodeType(node, ast_nodetype::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_division) node) {
			checkNodeType(node, ast_nodetype::DIVISION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_equality) node) {
			checkNodeType(node, ast_nodetype::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_for) node) {
			checkNodeType(node, ast_nodetype::FOR);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
			node->getIncrement()->accept(shared_from_this());
			node->getInitExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greater) node) {
			checkNodeType(node, ast_nodetype::GREATER_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greaterorequal) node) {
			checkNodeType(node, ast_nodetype::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_if) node) {
			checkNodeType(node, ast_nodetype::IF);

			node->getCondition()->accept(shared_from_this());
			node->getIfBody()->accept(shared_from_this());
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_less) node) {
			checkNodeType(node, ast_nodetype::LESS_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_lessorequal) node) {
			checkNodeType(node, ast_nodetype::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_and) node) {
			checkNodeType(node, ast_nodetype::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_or) node) {
			checkNodeType(node, ast_nodetype::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_multiplication) node) {
			checkNodeType(node, ast_nodetype::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_nonequality) node) {
			checkNodeType(node, ast_nodetype::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_parens) node) {
			checkNodeType(node, ast_nodetype::PARENS);

			node->getExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_return) node) {
			checkNodeType(node, ast_nodetype::RETURN);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_subtraction) node) {
			checkNodeType(node, ast_nodetype::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_string) node) {
			checkNodeType(node, ast_nodetype::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_symbol) node) {
			checkNodeType(node, ast_nodetype::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_while) node) {
			checkNodeType(node, ast_nodetype::WHILE);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
		}
	}

}
