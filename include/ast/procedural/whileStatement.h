#pragma once

#include <memory>
#include "ast/node.h"
#include "ast/procedural/abstractStatement.h"
#include "ast/procedural/assignmentExpression.h"
#include "ast/procedural/compoundBody.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CWhileStatement
		 * \brief Class for while-loop representation
		 */
		class CWhileStatement : public CAbstractStatement {
		  private:
			/**< Condition node */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_condition;

			/**< Body */
			std::shared_ptr<ast::procedural::CCompoundBody> m_body;

		  public:
			/**
			* Parametric constructor with default values
			* @param cond: condition node pointer
			* @param body: reference to vector of body nodes
			*/
			CWhileStatement(std::shared_ptr<ast::procedural::CAbstractExpression> cond = nullptr,
			                std::shared_ptr<ast::procedural::CCompoundBody> body = nullptr);

			/**
                        * Accept method for visitor acceptation.
                        * @param visitor: Pointer to abstract visitor.
                        */
                        virtual void accept(ast::visitors::CAbstractStringVisitor *visitor);

			/**
			* Body getter
			* @return Constant pointer to body
			*/
			std::shared_ptr<ast::procedural::CCompoundBody> getBody() const;

			/**
			* Condition getter
			* @return Pointer to condition node
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getCondition() const;
		};

	}

}