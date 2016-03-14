#pragma once

#include <memory>
#include "ast/procedural/abstractExpression.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

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
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor) = 0;
		};

	}

}