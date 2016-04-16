#include "ast/visitor/constantsVisitor.h"

namespace ast {

	namespace visitors {

                size_t CConstantsVisitor::getConstantsSize() const {
                    return m_constants.size();
                }

                std::shared_ptr<nodes::procedural::CAbstractPrimaryExpression> CConstantsVisitor::getConstantAt(size_t index) {
                    return m_constants.at(index);
                }
            
		/*---------------------- abstract nodes --------------------------*/
		void CConstantsVisitor::visit(ptr(ast_node) /*node*/) {
                    TRACE(ERROR, "Abstract node does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_bind) /*node*/) {
                    TRACE(ERROR, "Abstract bind does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_port) /*node*/) {
                    TRACE(ERROR, "Abstract port does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_expression) /*node*/) {
                    TRACE(ERROR, "Abstract expression does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_primaryexpression) /*node*/) {
                    TRACE(ERROR, "Abstract primary expression does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_statement) /*node*/) {
                    TRACE(ERROR, "Abstract statement does not contain any constant.");
		}
		void CConstantsVisitor::visit(ptr(ast_binary) /*node*/) {
                    TRACE(ERROR, "Abstract binary expression does not contain any constant.");
		}
		/*----------------------------------------------------------------*/

		void CConstantsVisitor::visit(ptr(ast_program) /*node*/) {
                    TRACE(ERROR, "Program does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_architecture) /*node*/) {
                    TRACE(ERROR, "Architecture does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_collectionportliteral) node) {
                    node->getIndexExpression()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_connection) node) {
                    node->getSourcePortIdentification()->accept(this->shared_from_this());
                    node->getDestinationPortIdentification()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_constraint) /*node*/) {
                    TRACE(ERROR, "Constraint does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_delegation) node) {
                    node->getSourcePortIdentification()->accept(this->shared_from_this());
                    node->getDestinationPortIdentification()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_dereference) /*node*/) {
                    TRACE(ERROR, "Dereference does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_descriptor) /*node*/) {
                    TRACE(ERROR, "Descriptor does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_disconnection) node) {
                    node->getSourcePortIdentification()->accept(this->shared_from_this());
                    node->getDestinationPortIdentification()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_injectedport) /*node*/) {
                    TRACE(ERROR, "Injected port does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_interface) /*node*/) {
                    TRACE(ERROR, "Interface does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_namedport) /*node*/) {
                    TRACE(ERROR, "Named port does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_portaddress) node) {
                    node->getComponent()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_service) node) {
                    for (size_t i = 0; i < node->getBodySize(); ++i) {
                        node->getBodyNodeAt(i)->accept(this->shared_from_this());
                    }
		}

		void CConstantsVisitor::visit(ptr(ast_serviceinvocation) node) {
                    if (node->getIndex().use_count()) {
                        node->getIndex()->accept(this->shared_from_this());
                    }
                    node->getParameters()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_servicesignature) node) {
                    for (size_t i = 0; i < node->getParamsSize(); ++i) {
                        node->getParamAt(i)->accept(this->shared_from_this());
                    }
		}

		void CConstantsVisitor::visit(ptr(ast_signaturesport) /*node*/) {
                    TRACE(ERROR, "Signatures port does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_universalport) /*node*/) {
                    TRACE(ERROR, "Universal port does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_addition) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_assignment) node) {
                    node->getRightSide()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_break) /*node*/) {
                    TRACE(ERROR, "Break does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_compound) node) {
                    for (size_t i = 0; i < node->getBodySize(); ++i) {
                        node->getBodyNodeAt(i)->accept(this->shared_from_this());
                    }
		}

		void CConstantsVisitor::visit(ptr(ast_constant) node) {
                    m_constants.push_back(node);
		}

                void CConstantsVisitor::visit(ptr(ast_boolean) node) {
                    m_constants.push_back(node);
		}
                
		void CConstantsVisitor::visit(ptr(ast_continue) /*node*/) {
                    TRACE(ERROR, "Continue does not contain any constant.");
		}

		void CConstantsVisitor::visit(ptr(ast_division) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_equality) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_for) node) {
                    node->getInitExpression()->accept(this->shared_from_this());
                    node->getCondition()->accept(this->shared_from_this());
                    node->getIncrement()->accept(this->shared_from_this());
                    node->getBody()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_greater) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_greaterorequal) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_if) node) {
                    node->getCondition()->accept(this->shared_from_this());
                    node->getIfBody()->accept(this->shared_from_this());
                    if (node->getElseBody().use_count()) {
                        node->getElseBody()->accept(this->shared_from_this());
                    }
		}

		void CConstantsVisitor::visit(ptr(ast_less) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_lessorequal) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_and) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_or) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_multiplication) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_nonequality) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_parens) node) {
                    node->getExpression()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_return) node) {
                    node->getExpression()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_subtraction) node) {
                    node->getOperand1()->accept(this->shared_from_this());
                    node->getOperand2()->accept(this->shared_from_this());
		}

		void CConstantsVisitor::visit(ptr(ast_string) node) {
                    m_constants.push_back(node);
		}

		void CConstantsVisitor::visit(ptr(ast_symbol) /*node*/) {
		}

		void CConstantsVisitor::visit(ptr(ast_while) node) {
                    node->getCondition()->accept(this->shared_from_this());
                    node->getBody()->accept(this->shared_from_this());
		}
	}

}
