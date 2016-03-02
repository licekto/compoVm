#pragma once

#include <memory>
#include "abstractStatement.h"
#include "compoundBody.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CIfStatement : public CAbstractStatement {
		  private:
			std::shared_ptr<nodes::procedural::CAbstractExpression> m_condition; /**< Start condition node */
			std::shared_ptr<nodes::procedural::CCompoundBody> m_ifBody; /**< If body */
                        std::shared_ptr<nodes::procedural::CCompoundBody> m_elseBody; /**< Else body */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CIfStatement(std::shared_ptr<nodes::procedural::CAbstractExpression> condition = nullptr,
			             std::shared_ptr<nodes::procedural::CCompoundBody> ifBody = nullptr,
                                     std::shared_ptr<nodes::procedural::CCompoundBody> elseBody = nullptr);

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void print(std::ostream& os) const;

			/**
			* If body getter
			* @return Constant pointer to if body
			*/
			std::shared_ptr<nodes::procedural::CCompoundBody> getIfBody() const;

                        /**
			* Else body getter
			* @return Constant pointer to else body
			*/
			std::shared_ptr<nodes::procedural::CCompoundBody> getElseBody() const;
                        
			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<nodes::procedural::CAbstractExpression> getCondition() const;
		};

	}

}