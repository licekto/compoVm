#pragma once

#include <memory>
#include "ast/nodes/procedural/abstractPrimaryExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CParens
			 * \brief Class for expression in parentheses.
			 */
			class CParens : public CAbstractPrimaryExpression, public std::enable_shared_from_this<CParens> {
			  private:
				/**< Expression in parentheses */
				std::shared_ptr<CNode> m_expression;

			  public:
				/**
				* Parametric constructor with default values
				* @param expr: expression
				*/
				CParens(std::shared_ptr<CNode> expr = nullptr);

				/**
				                * Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				 * Expression getter
				 * @return nodes::CNode pointer
				 */
				std::shared_ptr<CNode> getExpression() const;
			};

		}

	}

}