#pragma once

#include <memory>

#include "ast/nodes/procedural/binaryExpression.h"
#include "ast/nodes/types/operatorType.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CSubtractionExpression
			 * \brief Class for subtraction representation.
			 */
			class CSubtractionExpression : public CBinaryExpression, public std::enable_shared_from_this<CSubtractionExpression> {
			  public:
				/**
				* Parametric constructor with default values
				* @param variable: name of variable
				* @param rval: right-hand side of assignment
				*/
				CSubtractionExpression(std::shared_ptr<procedural::CAbstractExpression> op1 = nullptr,
				                       std::shared_ptr<procedural::CAbstractExpression> op2 = nullptr);

				/**
				* Accept method for visitor acceptation.
						* @param visitor: Pointer to abstract visitor.
						*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}