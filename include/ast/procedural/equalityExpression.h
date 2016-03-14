#pragma once

#include <memory>

#include "ast/procedural/binaryExpression.h"
#include "ast/types/operatorType.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CEqualityExpression
		 * \brief Class for equality representation.
		 */
		class CEqualityExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CEqualityExpression(std::shared_ptr<ast::procedural::CAbstractExpression> op1 = nullptr,
			                    std::shared_ptr<ast::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}