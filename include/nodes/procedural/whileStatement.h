#pragma once

#include <memory>
#include "nodes/node.h"
#include "abstractStatement.h"
#include "assignmentExpression.h"
#include "compoundBody.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CWhileStatement : public CAbstractStatement {
		  private:
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_condition; /**< Start condition node */
			std::shared_ptr<nodes::procedural::CCompoundBody> m_body; /**< Body */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
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