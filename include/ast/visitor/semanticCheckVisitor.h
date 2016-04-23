#pragma once

#include <memory>

#include "abstractVisitor.h"
#include "definitions/allDefinitions.h"

#include "types.h"

#include "exceptions/semantic/wrongAstNodeTypeException.h"
#include "exceptions/semantic/emptyProgramException.h"
#include "exceptions/semantic/undefinedDescriptorException.h"
#include "exceptions/semantic/undefinedInterfaceException.h"
#include "ast/semantic/syntaxDescriptorsTable.h"
#include "exceptions/semantic/wrongBaseTypeException.h"
#include "exceptions/semantic/undefinedPortException.h"
#include "exceptions/semantic/unsupportedFeatureException.h"
#include "exceptions/semantic/bidirectionalPortNotSupportedException.h"

namespace ast {

	namespace visitors {

		/**
		* \class CAbstractVisitor
		* \brief Abstract base class (interface) for other visitors.
		*
		* Abstract base class for visitors servers as interface. Every visitor derived from this one.
		*/
		class CSemanticCheckVisitor : public CAbstractVisitor, public std::enable_shared_from_this<CSemanticCheckVisitor> {
		  private:

			ptr(ast::semantic::CSyntaxDescriptorTable) m_descriptorTable;

			ptr(ast_descriptor) m_currentDescriptor;

			void checkDescriptorInterface(ptr(ast_descriptorinterface) node);

			void checkNodeType(ptr(ast_node) node, type_node type);
		  public:

			CSemanticCheckVisitor(ptr(ast::semantic::CSyntaxDescriptorTable) descriptorTable = nullptr);

			virtual void visit(ptr(ast_node) node);
			virtual void visit(ptr(ast_program) node);

			virtual void visit(ptr(ast_architecture) node);
			virtual void visit(ptr(ast_bind) node);
			virtual void visit(ptr(ast_collectionportliteral) node);
			virtual void visit(ptr(ast_connection) node);
			virtual void visit(ptr(ast_constraint) node);
			virtual void visit(ptr(ast_delegation) node);
			virtual void visit(ptr(ast_dereference) node);
			virtual void visit(ptr(ast_descriptor) node);
			virtual void visit(ptr(ast_disconnection) node);
			virtual void visit(ptr(ast_injectedport) node);
			virtual void visit(ptr(ast_interface) node);
			virtual void visit(ptr(ast_namedport) node);
			virtual void visit(ptr(ast_port) node);
			virtual void visit(ptr(ast_portaddress) node);
			virtual void visit(ptr(ast_service) node);
			virtual void visit(ptr(ast_serviceinvocation) node);
			virtual void visit(ptr(ast_servicesignature) node);
			virtual void visit(ptr(ast_signaturesport) node);
			virtual void visit(ptr(ast_sizeof) node);
			virtual void visit(ptr(ast_universalport) node);

			virtual void visit(ptr(ast_expression) node);
			virtual void visit(ptr(ast_primaryexpression) node);
			virtual void visit(ptr(ast_statement) node);
			virtual void visit(ptr(ast_addition) node);
			virtual void visit(ptr(ast_assignment) node);
			virtual void visit(ptr(ast_binary) node);
			virtual void visit(ptr(ast_break) node);
			virtual void visit(ptr(ast_compound) node);
			virtual void visit(ptr(ast_constant) node);
			virtual void visit(ptr(ast_boolean) node);
			virtual void visit(ptr(ast_continue) node);
			virtual void visit(ptr(ast_division) node);
			virtual void visit(ptr(ast_equality) node);
			virtual void visit(ptr(ast_for) node);
			virtual void visit(ptr(ast_greater) node);
			virtual void visit(ptr(ast_greaterorequal) node);
			virtual void visit(ptr(ast_if) node);
			virtual void visit(ptr(ast_less) node);
			virtual void visit(ptr(ast_lessorequal) node);
			virtual void visit(ptr(ast_and) node);
			virtual void visit(ptr(ast_or) node);
			virtual void visit(ptr(ast_multiplication) node);
			virtual void visit(ptr(ast_nonequality) node);
			virtual void visit(ptr(ast_parens) node);
			virtual void visit(ptr(ast_return) node);
			virtual void visit(ptr(ast_subtraction) node);
			virtual void visit(ptr(ast_string) node);
			virtual void visit(ptr(ast_symbol) node);
			virtual void visit(ptr(ast_while) node);
		};
	}
}