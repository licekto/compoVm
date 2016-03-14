#pragma once

#include <memory>

#include "ast/procedural/binaryExpression.h"
#include "ast/types/operatorType.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CLessOrEqualExpression
		 * \brief Class for '<=' representation.
		 */
		class CLessOrEqualExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CLessOrEqualExpression(std::shared_ptr<ast::procedural::CAbstractExpression> op1 = nullptr,
			                       std::shared_ptr<ast::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}