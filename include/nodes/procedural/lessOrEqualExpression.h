#pragma once

#include <memory>

#include "nodes/procedural/binaryExpression.h"
#include "nodes/types/operatorType.h"

namespace nodes {

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
			CLessOrEqualExpression         ( std::shared_ptr<nodes::procedural::CAbstractExpression> op1 = nullptr,
			                                 std::shared_ptr<nodes::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}