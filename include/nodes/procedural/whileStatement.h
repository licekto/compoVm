#pragma once

#include <memory>
#include "nodes/node.h"
#include "abstractStatement.h"
#include "assignmentExpression.h"
#include "compoundBody.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CWhileStatement
		 * \brief Class for while-loop representation
		 */
		class CWhileStatement : public CAbstractStatement {
		  private:
			/**< Condition node */
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_condition;

			/**< Body */
			std::shared_ptr<nodes::procedural::CCompoundBody> m_body;

		  public:
			/**
			* Parametric constructor with default values
			* @param cond: condition node pointer
			* @param body: reference to vector of body nodes
			*/
			CWhileStatement(std::shared_ptr<nodes::procedural::CAbstractExpression> cond = nullptr,
			                std::shared_ptr<nodes::procedural::CCompoundBody> body = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* Body getter
			* @return Constant pointer to body
			*/
			std::shared_ptr<nodes::procedural::CCompoundBody> getBody() const;

			/**
			* Condition getter
			* @return Pointer to condition node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression> getCondition() const;
		};

	}

}