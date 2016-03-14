#pragma once

#include <memory>
#include "abstractPrimaryExpression.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CParens
		 * \brief Class for expression in parentheses.
		 */
		class CParens : public CAbstractPrimaryExpression {
		  private:
			/**< Expression in parentheses */
			std::shared_ptr<ast::CNode> m_expression;

		  public:
			/**
			* Parametric constructor with default values
			* @param type: type of node
			* @param val: integer value
			*/
			CParens(std::shared_ptr<ast::CNode> expr = nullptr);

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			 * Expression getter
			 * @return nodes::CNode pointer
			 */
			std::shared_ptr<ast::CNode> getExpression() const;
		};

	}

}