#pragma once

#include <memory>
#include "ast/nodes/procedural/abstractExpression.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CAbstractPrimaryExpression
			 * \brief Class for primary expression like string literal, constant, identifier or expression in parentheses.
			 */
			class CAbstractPrimaryExpression : public virtual CAbstractExpression {
			  public:

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;
			};

		}

	}

}