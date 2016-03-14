#pragma once

#include <memory>
#include "abstractPrimaryExpression.h"


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
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& outStr) const;

			/**
			 * Expression getter
			 * @return nodes::CNode pointer
			 */
			std::shared_ptr<ast::CNode> getExpression() const;
		};

	}

}