#pragma once

#include <memory>
#include "ast/procedural/abstractExpression.h"
#include "ast/types/operatorType.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

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
			std::shared_ptr<ast::procedural::CAbstractExpression> m_operand1;

			/**< Second operand */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_operand2;

			/**
			* Parametric constructor with default values
			* @param variable: name of variable
			* @param rval: right-hand side of assignment
			*/
			CBinaryExpression         ( types::operatorType type = types::operatorType::PLUS,
			                            std::shared_ptr<ast::procedural::CAbstractExpression> op1 = nullptr,
			                            std::shared_ptr<ast::procedural::CAbstractExpression> op2 = nullptr);

		  public:
			
                        /**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			* Operator getter
			* @return Operator type
			*/
			types::operatorType getOperator () const;

			/**
			* First operand getter
			* @return Operand expression pointer
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getOperand1() const;

			/**
			* Second operand getter
			* @return Operand expression pointer
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getOperand2() const;
		};

	}

}