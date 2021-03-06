#pragma once

#include <memory>

#include "ast/nodes/procedural/binaryExpression.h"
#include "types.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CAdditionExpression
			 * \brief Class for addition representation.
			 */
			class CAdditionExpression : public CBinaryExpression, public std::enable_shared_from_this<CAdditionExpression> {
			  public:
				/**
				* Parametric constructor with default values
				* @param op1: first operand
				* @param op2: second operand
				*/
				CAdditionExpression(std::shared_ptr<CNode> op1 = nullptr,
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