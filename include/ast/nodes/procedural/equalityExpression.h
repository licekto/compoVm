#pragma once

#include <memory>

#include "ast/nodes/procedural/binaryExpression.h"
#include "ast/nodes/types/operatorType.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CEqualityExpression
			 * \brief Class for equality representation.
			 */
			class CEqualityExpression : public CBinaryExpression, public std::enable_shared_from_this<CEqualityExpression> {
			  public:
				/**
				* Parametric constructor with default values
				* @param variable: name of variable
				* @param rval: right-hand side of assignment
				*/
				CEqualityExpression(std::shared_ptr<procedural::CAbstractExpression> op1 = nullptr,
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