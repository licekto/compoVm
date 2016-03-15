#pragma once

#include <memory>

#include "ast/procedural/binaryExpression.h"
#include "ast/types/operatorType.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CDivisionExpression
		 * \brief Class for division representation.
		 */
		class CDivisionExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CDivisionExpression(std::shared_ptr<ast::procedural::CAbstractExpression> op1 = nullptr,
			                    std::shared_ptr<ast::procedural::CAbstractExpression> op2 = nullptr);

			/**
			* Accept method for visitor acceptation.
					* @param visitor: Pointer to abstract visitor.
					*/
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);
		};

	}

}