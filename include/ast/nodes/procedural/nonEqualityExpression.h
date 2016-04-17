#pragma once

#include <memory>

#include "ast/nodes/procedural/binaryExpression.h"
#include "types.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CNonEqualityExpression
			 * \brief Class for non-equality representation.
			 */
			class CNonEqualityExpression : public CBinaryExpression, public std::enable_shared_from_this<CNonEqualityExpression> {
			  public:
				/**
				* Parametric constructor with default values
				* @param variable: name of variable
				* @param rval: right-hand side of assignment
				*/
				CNonEqualityExpression(std::shared_ptr<CNode> op1 = nullptr,
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