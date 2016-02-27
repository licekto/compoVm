#pragma once

#include "nodes/node.h"

namespace nodes {

	namespace procedural {

		/**
		 * \class CFor
		 * \brief Class for for-loop representation
		 */
		class CFor : public CNode {
		  private:
			CNode                    * m_startCondition;           /**< Start condition node */
			CNode                    * m_endCondition;             /**< Start condition node */
			CNode                    * m_step;                     /**< Step node */
			std::vector<CNode*>        m_body;                     /**< Body nodes vector */

		  public:
			/**
			* Parametric constructor with default value
			* @param startCond: Star condition node pointer
			* @param endCond: Star condition node pointer
			* @param step: Step node pointer
			* @param body: Reference to vector of body nodes
			*/
			CFor                ( CNode *startCond = nullptr,
			                      CNode *endCond = nullptr,
			                      CNode *step = nullptr,
			                      const std::vector<CNode*>& body = std::vector<CNode*>(0));
			\
			/**
			* Copy constructor
			* @param other: reference to another object of same type
			*/
			CFor                (const CFor& other);

			/**
			* Move constructor
			* @param other: rvalue-reference to another object of same type
			*/
			CFor                (CFor&& other) noexcept;

			/**
			* Copy assignment operator
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CFor&                           operator =          (const CFor& other);

			/**
			* Move assignment operator
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CFor&                           operator =          (CFor&& other) noexcept;

			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual CNode *                    clone               () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CFor               ();

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
			CNode *                    getBodyNodeAt       (int index) const;

			/**
			* Start condition getter
			* @return Pointer to start condition node
			*/
			CNode *                    getStartCond        () const;

			/**
			* End condition getter
			* @return Pointer to end condition node
			*/
			CNode *                    getEndCond          () const;

			/**
			* Step getter
			* @return Pointer to step node
			*/
			CNode *                    getStep             () const;
		};

	}

}