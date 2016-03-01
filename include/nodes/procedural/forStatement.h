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
		class CForStatement : public CAbstractStatement {
		  private:
			std::shared_ptr<nodes::procedural::CAssignmentExpression>    m_startCondition;           /**< Start condition node */
			std::shared_ptr<nodes::procedural::CAbstractExpression>    m_endCondition;             /**< Start condition node */
			std::shared_ptr<nodes::procedural::CAbstractExpression>    m_step;                     /**< Step node */
			std::shared_ptr<nodes::procedural::CCompoundBody> m_body;                     /**< Body */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CForStatement                ( std::shared_ptr<nodes::procedural::CAssignmentExpression> startCond = nullptr,
			                               std::shared_ptr<nodes::procedural::CAbstractExpression> endCond = nullptr,
			                               std::shared_ptr<nodes::procedural::CAbstractExpression> step = nullptr,
			                               std::shared_ptr<nodes::procedural::CCompoundBody> body = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Body getter
			* @return Constant pointer to body
			*/
			std::shared_ptr<nodes::procedural::CCompoundBody>                    getBody () const;

			/**
			* Start condition getter
			* @return Pointer to start condition node
			*/
			std::shared_ptr<nodes::procedural::CAssignmentExpression>                    getStartCond        () const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression>                    getEndCond          () const;

			/**
			* Step getter
			* @return Pointer to step node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression>                    getStep             () const;
		};

	}

}