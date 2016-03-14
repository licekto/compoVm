#pragma once

#include <memory>
#include "ast/procedural/abstractStatement.h"
#include "ast/procedural/compoundBody.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace procedural {

		/**
		 * \class CIfStatement
		 * \brief Class for if statement representation
		 */
		class CIfStatement : public CAbstractStatement {
		  private:
			/**< Start condition node */
			std::shared_ptr<ast::procedural::CAbstractExpression> m_condition;

			/**< If body */
			std::shared_ptr<ast::procedural::CCompoundBody> m_ifBody;

			/**< Else body */
			std::shared_ptr<ast::procedural::CCompoundBody> m_elseBody;

		  public:
			/**
			* Parametric constructor with default value
			* @param condition: condition node pointer
			            * @param ifBody: if branch body node
			            * @param elseBody: else branch body node
			*/
			CIfStatement(std::shared_ptr<ast::procedural::CAbstractExpression> condition = nullptr,
			             std::shared_ptr<ast::procedural::CCompoundBody> ifBody = nullptr,
			             std::shared_ptr<ast::procedural::CCompoundBody> elseBody = nullptr);

			/**
			            * Accept method for visitor acceptation.
			            * @param visitor: Pointer to abstract visitor.
			            */
			virtual void accept(ast::visitors::CAbstractVisitor *visitor);

			/**
			* If body getter
			* @return Constant pointer to if body
			*/
			std::shared_ptr<ast::procedural::CCompoundBody> getIfBody() const;

			/**
			* Else body getter
					* @return Constant pointer to else body
					*/
			std::shared_ptr<ast::procedural::CCompoundBody> getElseBody() const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<ast::procedural::CAbstractExpression> getCondition() const;
		};

	}

}