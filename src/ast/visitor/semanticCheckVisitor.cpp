#include "ast/visitor/semanticCheckVisitor.h"

namespace ast {

	namespace visitors {
            
                CSemanticCheckVisitor::CSemanticCheckVisitor(ptr(ast::semantic::CGlobalDescriptorTable) descriptorTable) 
                : m_descriptorTable(descriptorTable) {

                }
            
		void CSemanticCheckVisitor::checkDescriptorArchitecture(ptr(ast_descriptor) node) {
                    if (m_descriptorTable.use_count()) {
			if (!m_descriptorTable->symbolFound(node->getNameSymbol()->getStringValue())) {
				throw exceptions::semantic::CUndefinedDescriptorException(node->getNameSymbol()->getStringValue());
			}

			if (node->getExtendsSymbol().use_count() && !m_descriptorTable->symbolFound(node->getExtendsSymbol()->getStringValue())) {
				throw exceptions::semantic::CUndefinedDescriptorException(node->getExtendsSymbol()->getStringValue());
			}
                        
                        
                    }
		}

		void CSemanticCheckVisitor::checkNodeType(ptr(ast_node) node, ast_type type) {
			if (!IS_TYPE(node, type)) {
				throw exceptions::semantic::CWrongAstNodeTypeException(type, node->getNodeType());
			}
		}

		/*---------------------- abstract nodes --------------------------*/
		void CSemanticCheckVisitor::visit(ptr(ast_node) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_reqprov) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_servconstr) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_bind) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_port) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_expression) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_primaryexpression) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_statement) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		void CSemanticCheckVisitor::visit(ptr(ast_binary) node) {
			checkNodeType(node, ast_type::CONSTRAINT);
		}
		/*----------------------------------------------------------------*/

		void CSemanticCheckVisitor::visit(ptr(ast_program) node) {
			checkNodeType(node, ast_type::PROGRAM);

			if (node->getNodesSize() == 0) {
				throw exceptions::semantic::CEmptyProgramException();
			}

			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_architecture) node) {
			checkNodeType(node, ast_type::ARCHITECTURE);

			if (node->getBodySize() == 0) {
				// warning, empty architecture
			}

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_collectionportliteral) node) {
			checkNodeType(node, ast_type::COLLECTION_PORT);

			node->getPortName()->accept(shared_from_this());
			node->getIndexExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_connection) node) {
			checkNodeType(node, ast_type::CONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_constraint) node) {
			checkNodeType(node, ast_type::CONSTRAINT);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_delegation) node) {
			checkNodeType(node, ast_type::DELEGATION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_dereference) node) {
			checkNodeType(node, ast_type::DEREFERENCE);

			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_descriptor) node) {
			checkNodeType(node, ast_type::DESCRIPTOR);

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

			checkDescriptorArchitecture(node);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_disconnection) node) {
			checkNodeType(node, ast_type::DISCONNECTION);

			node->getPortIdentification1()->accept(shared_from_this());
			node->getPortIdentification2()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_injectedport) node) {
			checkNodeType(node, ast_type::INJECTED_PORT);

			node->getInjectedWith()->accept(shared_from_this());
			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_interface) node) {
			checkNodeType(node, ast_type::INTERFACE);

			node->getExtendsSymbol()->accept(shared_from_this());
			node->getNameSymbol()->accept(shared_from_this());

			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_namedport) node) {
			checkNodeType(node, ast_type::NAMED_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			node->getParamName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_portaddress) node) {
			checkNodeType(node, ast_type::PORT_ADDRESS);

			node->getComponent()->accept(shared_from_this());
			node->getPortName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_provision) node) {
			checkNodeType(node, ast_type::PROVISION);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_requirement) node) {
			checkNodeType(node, ast_type::REQUIREMENT);

			for (size_t i = 0; i < node->getNumberOfPorts(); ++i) {
				node->getPortAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_service) node) {
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

		void CSemanticCheckVisitor::visit(ptr(ast_serviceinvocation) node) {
			checkNodeType(node, ast_type::SERVICE_INVOCATION);

			node->getParameters()->accept(shared_from_this());
			node->getReceiverName()->accept(shared_from_this());
			node->getSelectorName()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_servicesignature) node) {
			checkNodeType(node, ast_type::SERVICE_SIGNATURE);

			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_signaturesport) node) {
			checkNodeType(node, ast_type::SIGNATURES_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
			for (size_t i = 0; i < node->getSignaturesSize(); ++i) {
				node->getSignatureAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_universalport) node) {
			checkNodeType(node, ast_type::UNIVERSAL_PORT);

			if (node->getKindOf()) {
				node->getKindOf()->accept(shared_from_this());
			}
			node->getNameSymbol()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_addition) node) {
			checkNodeType(node, ast_type::ADDITION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_assignment) node) {
			checkNodeType(node, ast_type::ASSIGNMENT_EXPRESSION);

			node->getRValue()->accept(shared_from_this());
			node->getVariable()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_break) node) {
			checkNodeType(node, ast_type::BREAK);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_compound) node) {
			checkNodeType(node, ast_type::COMPOUND_BODY);

			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(shared_from_this());
			}

			for (size_t i = 0; i < node->getTemporariesSize(); ++i) {
				node->getTemporaryAt(i)->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_constant) node) {
			checkNodeType(node, ast_type::CONSTANT);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_continue) node) {
			checkNodeType(node, ast_type::CONTINUE);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_division) node) {
			checkNodeType(node, ast_type::DIVISION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_equality) node) {
			checkNodeType(node, ast_type::EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_for) node) {
			checkNodeType(node, ast_type::FOR);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
			node->getIncrement()->accept(shared_from_this());
			node->getInitExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greater) node) {
			checkNodeType(node, ast_type::GREATER_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_greaterorequal) node) {
			checkNodeType(node, ast_type::GREATER_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_if) node) {
			checkNodeType(node, ast_type::IF);

			node->getCondition()->accept(shared_from_this());
			node->getIfBody()->accept(shared_from_this());
			if (node->getElseBody() != nullptr) {
				node->getElseBody()->accept(shared_from_this());
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_less) node) {
			checkNodeType(node, ast_type::LESS_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_lessorequal) node) {
			checkNodeType(node, ast_type::LESS_OR_EQUAL_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_and) node) {
			checkNodeType(node, ast_type::LOGICAL_AND_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_or) node) {
			checkNodeType(node, ast_type::LOGICAL_OR_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_multiplication) node) {
			checkNodeType(node, ast_type::MULTIPLICATION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_nonequality) node) {
			checkNodeType(node, ast_type::NON_EQUALITY_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_parens) node) {
			checkNodeType(node, ast_type::PARENS);

			node->getExpression()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_return) node) {
			checkNodeType(node, ast_type::RETURN);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_subtraction) node) {
			checkNodeType(node, ast_type::SUBTRACTION_EXPRESSION);

			node->getOperand1()->accept(shared_from_this());
			node->getOperand1()->accept(shared_from_this());
		}

		void CSemanticCheckVisitor::visit(ptr(ast_string) node) {
			checkNodeType(node, ast_type::STRING_LITERAL);
		}

		void CSemanticCheckVisitor::visit(ptr(ast_symbol) node) {
			checkNodeType(node, ast_type::SYMBOL);

			if (node->getStringValue() == "") {
				// warning, empty symbol??
			}
		}

		void CSemanticCheckVisitor::visit(ptr(ast_while) node) {
			checkNodeType(node, ast_type::WHILE);

			node->getBody()->accept(shared_from_this());
			node->getCondition()->accept(shared_from_this());
		}
	}

}
