#pragma once

#include <memory>

#include "nodes/procedural/binaryExpression.h"
#include "nodes/types/operatorType.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CGreaterOrEqualExpression
		 * \brief Class for addition representation.
		 */
		class CGreaterOrEqualExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CGreaterOrEqualExpression         ( std::shared_ptr<nodes::procedural::CAbstractExpression> op1 = nullptr,
			                              std::shared_ptr<nodes::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}