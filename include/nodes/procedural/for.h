#pragma once

#include <memory>
#include "nodes/node.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CFor : public CNode {
		  private:
			std::shared_ptr<nodes::CNode>    m_startCondition;           /**< Start condition node */
			std::shared_ptr<nodes::CNode>    m_endCondition;             /**< Start condition node */
			std::shared_ptr<nodes::CNode>    m_step;                     /**< Step node */
			std::vector<std::shared_ptr<nodes::CNode>>        m_body;                     /**< Body nodes vector */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CFor                ( std::shared_ptr<nodes::CNode> startCond = nullptr,
			                      std::shared_ptr<nodes::CNode> endCond = nullptr,
			                      std::shared_ptr<nodes::CNode> step = nullptr,
			                      const std::vector<std::shared_ptr<nodes::CNode>>& body = std::vector<std::shared_ptr<nodes::CNode>>(0));

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print               (std::ostream& os) const;

			/**
			* Body getter
			* @return Constant pointer to body vector
			*/
			std::shared_ptr<nodes::CNode>                    getBodyNodeAt       (int index) const;

			/**
			* Start condition getter
			* @return Pointer to start condition node
			*/
			std::shared_ptr<nodes::CNode>                    getStartCond        () const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			std::shared_ptr<nodes::CNode>                    getEndCond          () const;

			/**
			* Step getter
			* @return Pointer to step node
			*/
			std::shared_ptr<nodes::CNode>                    getStep             () const;
		};

	}

}