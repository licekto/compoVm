#pragma once

#include <memory>
#include "ast/nodes/procedural/abstractExpression.h"
#include "types.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CBinaryExpression
			 * \brief Class for binary expression representation.
			 */
			class CBinaryExpression : public virtual CAbstractExpression {
			  protected:
				/**< Operator */
				types::operatorType m_operator;

				/**< First operand */
				std::shared_ptr<CNode> m_operand1;

				/**< Second operand */
				std::shared_ptr<CNode> m_operand2;

				/**
				* Parametric constructor with default values
				* @param variable: name of variable
				* @param rval: right-hand side of assignment
				*/
				CBinaryExpression(types::operatorType type = types::operatorType::PLUS,
				                  std::shared_ptr<CNode> op1 = nullptr,
				                  std::shared_ptr<CNode> op2 = nullptr);

			  public:

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;

				/**
				* Operator getter
				* @return Operator type
				*/
				types::operatorType getOperator () const;

				/**
				* First operand getter
				* @return Operand expression pointer
				*/
				std::shared_ptr<CNode> getOperand1() const;

				/**
				* Second operand getter
				* @return Operand expression pointer
				*/
				std::shared_ptr<CNode> getOperand2() const;
			};

		}

	}

}