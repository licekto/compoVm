#pragma once

#include <memory>

#include "ast/nodes/procedural/binaryExpression.h"
#include "types.h"

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
				* @param op1: first operand
				* @param op2: second operand
				*/
				CSubtractionExpression(std::shared_ptr<CNode> op1 = nullptr,
				                       std::shared_ptr<CNode> op2 = nullptr);

				/**
				* Accept method for visitor acceptation.
				                * @param visitor: Pointer to abstract visitor.
				                */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);
			};

		}

	}

}