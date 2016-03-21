#pragma once

#include <memory>
#include "ast/nodes/node.h"
#include "ast/nodes/procedural/abstractStatement.h"
#include "ast/nodes/procedural/assignmentExpression.h"
#include "ast/nodes/procedural/compoundBody.h"
#include "ast/visitor/abstractVisitor.h"

namespace ast {

	namespace nodes {

		namespace procedural {

			/**
			 * \class CWhileStatement
			 * \brief Class for while-loop representation
			 */
			class CWhileStatement : public CAbstractStatement, public std::enable_shared_from_this<CWhileStatement> {
			  private:
				/**< Condition node */
				std::shared_ptr<procedural::CAbstractExpression> m_condition;

				/**< Body */
				std::shared_ptr<procedural::CCompoundBody> m_body;

			  public:
				/**
				* Parametric constructor with default values
				* @param cond: condition node pointer
				* @param body: reference to vector of body nodes
				*/
				CWhileStatement(std::shared_ptr<procedural::CAbstractExpression> cond = nullptr,
				                std::shared_ptr<procedural::CCompoundBody> body = nullptr);

				/**
				            * Accept method for visitor acceptation.
				            * @param visitor: Pointer to abstract visitor.
				            */
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor);

				/**
				* Body getter
				* @return Constant pointer to body
				*/
				std::shared_ptr<procedural::CCompoundBody> getBody() const;

				/**
				* Condition getter
				* @return Pointer to condition node
				*/
				std::shared_ptr<procedural::CAbstractExpression> getCondition() const;
			};

		}

	}

}