#pragma once

#include <memory>
#include "ast/procedural/abstractStatement.h"
#include "ast/procedural/assignmentExpression.h"
#include "ast/procedural/compoundBody.h"
#include "ast/visitor/abstractStringVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CForStatement
		 * \brief Class for for-loop representation
		 */
		class CForStatement : public CAbstractStatement {
		  private:
			/**< Start condition node */
			std::shared_ptr<ast::procedural::CAssignmentExpression> m_initExpression;

			/**< Start condition node */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_condition;

			/**< Step node */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_increment;

			/**< Body */
			std::shared_ptr<ast::procedural::CCompoundBody> m_body;

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CForStatement(std::shared_ptr<ast::procedural::CAssignmentExpression> initExpression = nullptr,
			              std::shared_ptr<ast::procedural::CAbstractExpression> condition = nullptr,
			              std::shared_ptr<ast::procedural::CAbstractExpression> increment = nullptr,
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
			* Start condition getter
			* @return Pointer to start condition node
			*/
			std::shared_ptr<ast::procedural::CAssignmentExpression> getInitExpression() const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getCondition() const;

			/**
			* Step getter
			* @return Pointer to step node
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getIncrement() const;
		};

	}

}