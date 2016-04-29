#include "ast/visitor/constantsVisitor.h"
#include "ast/visitor/printVisitor.h"

namespace ast {

	namespace visitors {
		CPrintVisitor::CPrintVisitor() : m_tabs(0) {
		}

		void CPrintVisitor::printTabs() {
			for (int i = 0; i < m_tabs; ++i) {
				m_output << "\t";
			}
		}

		std::string CPrintVisitor::getOutput() const {
			return m_output.str();
		}

		/*---------------------- abstract nodes --------------------------*/
		void CPrintVisitor::visit(ptr(ast_node) /*node*/) {
			TRACE(ERROR, "Abstract node cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_bind) /*node*/) {
			TRACE(ERROR, "Abstract bind cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_port) /*node*/) {
			TRACE(ERROR, "Abstract port cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_expression) /*node*/) {
			TRACE(ERROR, "Abstract expression cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_primaryexpression) /*node*/) {
			TRACE(ERROR, "Abstract primary expression cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_statement) /*node*/) {
			TRACE(ERROR, "Abstract statement cannot be printed.");
		}
		void CPrintVisitor::visit(ptr(ast_binary) /*node*/) {
			TRACE(ERROR, "Abstract binary expression cannot be printed.");
		}
		/*----------------------------------------------------------------*/

		void CPrintVisitor::visit(ptr(ast_program) node) {
			for (size_t i = 0; i < node->getNodesSize(); ++i) {
				node->getNodeAt(i)->accept(this->shared_from_this());
			}
		}

		void CPrintVisitor::visit(ptr(ast_architecture) node) {
			printTabs();
			m_output << "architecture {" << std::endl;
			++m_tabs;
			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this->shared_from_this());
			}
			--m_tabs;
			printTabs();
			m_output << "}" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_collectionportliteral) node) {
			node->getIndexExpression()->accept(this->shared_from_this());
			m_output << "collection" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_connection) node) {
			printTabs();
			m_output << "connect " << node->getSourcePortIdentification()->getPortName()->getStringValue() << "@" << " to ";
			m_output << node->getDestinationPortIdentification()->getPortName()->getStringValue() << "@" << ";" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_constraint) /*node*/) {
			TRACE(ERROR, "Constraint cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_delegation) node) {
			node->getSourcePortIdentification()->accept(this->shared_from_this());
			node->getDestinationPortIdentification()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_dereference) /*node*/) {
			TRACE(ERROR, "Dereference cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_descriptor) node) {
			m_output << "descriptor " << node->getNameSymbol()->getStringValue();
			if (node->getExtendsSymbol().use_count()) {
				m_output << " extends " << node->getExtendsSymbol()->getStringValue();
			}
			m_output << " {" << std::endl;
			++m_tabs;

			if (node->getArchitecture().use_count()) {
				node->getArchitecture()->accept(this->shared_from_this());
			}

			for (size_t i = 0; i < node->getServicesSize(); ++i) {
				node->getServiceAt(i)->accept(this->shared_from_this());
			}

			--m_tabs;
		}

		void CPrintVisitor::visit(ptr(ast_disconnection) node) {
			printTabs();
			m_output << "disconnect" << node->getSourcePortIdentification()->getPortName()->getStringValue() << "@" << " to ";
			m_output << node->getDestinationPortIdentification()->getPortName()->getStringValue() << "@" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_injectedport) /*node*/) {
			TRACE(ERROR, "Injected port cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_interface) /*node*/) {
			TRACE(ERROR, "Interface cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_namedport) /*node*/) {
			TRACE(ERROR, "Named port cannot be printed.");
			m_output << "named" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_portaddress) node) {
			node->getComponent()->accept(this->shared_from_this());
			m_output << "address" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_service) node) {
			printTabs();
			m_output << "service " << node->getNameSymbol()->getStringValue() << " {" << std::endl;
			++m_tabs;
			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this->shared_from_this());
			}
			--m_tabs;
			m_output << "}" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_serviceinvocation) /*node*/) {
			printTabs();
			m_output << "service invocation" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_servicesignature) node) {
			for (size_t i = 0; i < node->getParamsSize(); ++i) {
				node->getParamAt(i)->accept(this->shared_from_this());
			}
		}

		void CPrintVisitor::visit(ptr(ast_signaturesport) /*node*/) {
			TRACE(ERROR, "Signatures port cannot be printed.");
			m_output << "signs" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_sizeof) /*node*/) {
			m_output << "sizeof" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_universalport) /*node*/) {
			TRACE(ERROR, "Universal port cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_addition) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_assignment) /*node*/) {
			printTabs();
			m_output << "assignment" << std::endl;
		}

		void CPrintVisitor::visit(ptr(ast_break) /*node*/) {
			TRACE(ERROR, "Break cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_compound) node) {
			for (size_t i = 0; i < node->getBodySize(); ++i) {
				node->getBodyNodeAt(i)->accept(this->shared_from_this());
			}
		}

		void CPrintVisitor::visit(ptr(ast_constant) /*node*/) {
		}

		void CPrintVisitor::visit(ptr(ast_boolean) /*node*/) {
		}

		void CPrintVisitor::visit(ptr(ast_continue) /*node*/) {
			TRACE(ERROR, "Continue cannot be printed.");
		}

		void CPrintVisitor::visit(ptr(ast_division) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_equality) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_for) node) {
			node->getInitExpression()->accept(this->shared_from_this());
			node->getCondition()->accept(this->shared_from_this());
			node->getIncrement()->accept(this->shared_from_this());
			node->getBody()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_greater) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_greaterorequal) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_if) node) {
			node->getCondition()->accept(this->shared_from_this());
			node->getIfBody()->accept(this->shared_from_this());
			if (node->getElseBody().use_count()) {
				node->getElseBody()->accept(this->shared_from_this());
			}
		}

		void CPrintVisitor::visit(ptr(ast_less) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_lessorequal) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_and) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_or) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_multiplication) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_nonequality) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_parens) node) {
			node->getExpression()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_return) node) {
			node->getExpression()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_subtraction) node) {
			node->getOperand1()->accept(this->shared_from_this());
			node->getOperand2()->accept(this->shared_from_this());
		}

		void CPrintVisitor::visit(ptr(ast_string) /*node*/) {
		}

		void CPrintVisitor::visit(ptr(ast_symbol) /*node*/) {
		}

		void CPrintVisitor::visit(ptr(ast_while) node) {
			node->getCondition()->accept(this->shared_from_this());
			node->getBody()->accept(this->shared_from_this());
		}
	}

}
