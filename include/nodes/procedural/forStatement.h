#pragma once

#include <memory>
#include "abstractStatement.h"
#include "assignmentExpression.h"
#include "compoundBody.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CForStatement : public CAbstractStatement {
		  private:
                        /**< Start condition node */
			std::shared_ptr<nodes::procedural::CAssignmentExpression> m_initExpression;
                        
                        /**< Start condition node */
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_condition;
                        
                        /**< Step node */
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_increment;
                        
                        /**< Body */
			std::shared_ptr<nodes::procedural::CCompoundBody> m_body;

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CForStatement(std::shared_ptr<nodes::procedural::CAssignmentExpression> initExpression = nullptr,
			              std::shared_ptr<nodes::procedural::CAbstractExpression> condition = nullptr,
			              std::shared_ptr<nodes::procedural::CAbstractExpression> increment = nullptr,
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
			* Start condition getter
			* @return Pointer to start condition node
			*/
			std::shared_ptr<nodes::procedural::CAssignmentExpression> getInitExpression() const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression> getCondition() const;

			/**
			* Step getter
			* @return Pointer to step node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression> getIncrement() const;
		};

	}

}