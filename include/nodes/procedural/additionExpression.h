#pragma once

#include <memory>
#include "nodes/node.h"
#include "nodes/procedural/binaryExpression.h"
#include "nodes/procedural/symbol.h"
#include "nodes/types/operatorType.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CAdditiveExpression
		 * \brief Class for assignment representation.
		 */
		class CAdditionExpression : public CBinaryExpression {
		  public:
			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CAdditionExpression         ( std::shared_ptr<nodes::procedural::CAbstractExpression> op1 = nullptr,
			                              std::shared_ptr<nodes::procedural::CAbstractExpression> op2 = nullptr);
		};

	}

}