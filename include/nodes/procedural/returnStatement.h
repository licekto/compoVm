#pragma once

#include <memory>

#include "nodes/procedural/abstractStatement.h"
#include "nodes/procedural/abstractExpression.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CReturnStatement : public CAbstractStatement {
		  private:
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_expression; /**< Start condition node */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CReturnStatement(std::shared_ptr<nodes::procedural::CAbstractExpression> condition = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;
                        
			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression> getExpression() const;
		};

	}

}