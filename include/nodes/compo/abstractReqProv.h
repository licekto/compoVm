#pragma once

#include <exception>

#include "nodes/node.h"
#include "nodes/compo/port.h"
#include "nodes/types/visibilityType.h"

namespace nodes {

	/**
	 *  \addtogroup compo
	 *  @{
	 */

	/**
	 * compo Namespace to uniquely identify compo AST nodes.
	 */
	namespace compo {

		/**
		 * \class CAbstractReqProv
		 * \brief Abstract base class for requirement and provision nodes.
		 *
		 * Abstract base class for requirement and provision nodes. Class inherits virtually from nodes::CNode prevent diamond problem.
		 * This class was designed because of the same structure of provision a requirement nodes thus to prevent code repetition.
		 */
		class CAbstractReqProv : public virtual nodes::CNode {
		  protected:
			nodes::types::visibilityType                  m_visibilityType;   /**< Type of visibility */
			std::vector<compo::CPort*> m_ports;            /**< Vector of ports */

			/**
			* Parametric constructor with default values
			* Constructor is made protected to prevent from creation of object of this (abstract) type.
			* @param type: type of visibilty
			* @param ports: vector of ports
			*/
			CAbstractReqProv   (   nodes::types::visibilityType type = nodes::types::visibilityType::EXTERNAL,
			                       const std::vector<CPort*>& ports = std::vector<CPort*>(0));
			/**
			* Copy constructor
			* Copy constructor is made protected to prevent from copying of object of this (abstract) type.
			* @param other: reference to another object of same type
			*/
			CAbstractReqProv   (const CAbstractReqProv& other);

			/**
			* Move constructor
			* Move constructor is made protected to prevent from moving of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			*/
			CAbstractReqProv   (CAbstractReqProv&& other) noexcept;

			/**
			* Copy assignment operator
			* Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: reference to another object of same type
			* @return reference to assigned object
			*/
			CAbstractReqProv&          operator =              (const CAbstractReqProv& other);

			/**
			* Move assignment operator
			* Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
			* @param other: rvalue-reference to another object of same type
			* @return reference to assigned object
			*/
			CAbstractReqProv&          operator =              (CAbstractReqProv&& other) noexcept;

		  public:
			/**
			 * Clone method for copy-construction of polymorphic objects
			 * @return pointer to newly copied object.
			 */
			virtual nodes::CNode *                    clone                   () const;

			/**
			* Virtual destructor
			*/
			virtual                                 ~CAbstractReqProv  ();

			/**
			* Virtual print function to call from operator <<
			* @param os: output stream
			* @see operator <<()
			*/
			virtual void                            print                   (std::ostream& os) const;

			/**
			* nodes::types::visibilityType getter
			* @return Type of visibility
			*/
			nodes::types::visibilityType                  getVisibilityType       () const;

			/**
			* Number of ports getter
			* @return number of ports of requirement
			*/
			size_t                          getNumberOfPorts        () const;

			/**
			* Ports getter
			* @return Port at given index
			*/
			CPort *                    getPortAt               (unsigned int index) const;
		};

	}

}