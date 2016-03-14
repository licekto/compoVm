#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/symbol.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CAssignmentExpression
		 * \brief Class for assignment representation.
		 */
		class CAssignmentExpression : public CAbstractExpression {
		  protected:
			/**< Variable to assign to */
			std::shared_ptr<ast::procedural::CSymbol> m_variable;

			/**< Right-hand side of assignment expression */
			std::shared_ptr<ast::CNode> m_rValue;

		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CAssignmentExpression(std::shared_ptr<ast::procedural::CSymbol> variable = nullptr,
			                      std::shared_ptr<ast::CNode> rVal = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			* Variable name getter
			* @return Variable name
			*/
			std::shared_ptr<ast::procedural::CSymbol> getVariable() const;

			/**
			* Right-hand side expression getter
			* @return Expression node
			*/
			std::shared_ptr<ast::CNode> getRValue() const;
		};

	}

}