#pragma once

#include <exception>
#include <memory>

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
			std::vector<std::shared_ptr<nodes::compo::CPort> >  m_ports;            /**< Vector of ports */

			/**
			* Parametric constructor with default values
			* Constructor is made protected to prevent from creation of object of this (abstract) type.
			* @param type: type of visibilty
			* @param ports: vector of ports
			*/
			CAbstractReqProv   (   nodes::types::visibilityType type = nodes::types::visibilityType::EXTERNAL,
			                       const std::vector<std::shared_ptr<compo::CPort> >& ports = std::vector<std::shared_ptr<nodes::compo::CPort>>(0));

		  public:

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
			std::shared_ptr<nodes::compo::CPort>                    getPortAt               (unsigned int index) const;
		};

	}

}