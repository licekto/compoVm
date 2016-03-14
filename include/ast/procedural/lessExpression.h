#pragma once

#include <memory>

#include "ast/procedural/binaryExpression.h"
#include "ast/types/operatorType.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CLessExpression
		 * \brief Class for '<' representation.
		 */
		class CLessExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CLessExpression(std::shared_ptr<ast::procedural::CAbstractExpression> op1 = nullptr,
			                std::shared_ptr<ast::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}