#pragma once

#include <memory>

#include "ast/procedural/abstractStatement.h"
#include "ast/procedural/abstractExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CReturnStatement
		 * \brief Class for return statement representation
		 */
		class CReturnStatement : public CAbstractStatement {
		  private:
			/**< Start condition node */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_expression;

		  public:
			/**
			* Parametric constructor with default value
			* @param expression: expression smart pointer
			*/
			CReturnStatement(std::shared_ptr<ast::procedural::CAbstractExpression> expression = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getExpression() const;
		};

	}

}