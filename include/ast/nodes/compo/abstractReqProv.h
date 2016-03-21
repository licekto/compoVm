#pragma once

#include <exception>
#include <memory>

#include "ast/nodes/node.h"
#include "ast/nodes/compo/port.h"
#include "ast/nodes/types/visibilityType.h"

namespace ast {

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
			 * Abstract base class for requirement and provision nodes. Class inherits virtually from nodes::CNode to prevent diamond problem.
			 * This class was designed because of the same structure of provision a requirement nodes thus to prevent code repetition.
			 */
			class CAbstractReqProv : public virtual CNode {
			  protected:
				/**< Type of visibility */
				nodes::types::visibilityType m_visibilityType;

				/**< Vector of ports */
				std::vector<std::shared_ptr<compo::CPort>> m_ports;

				/**
				* Parametric constructor with default values
				* Constructor is made protected to prevent from creation of object of this (abstract) type.
				* @param type: type of visibility
				* @param ports: vector of ports
				*/
				CAbstractReqProv(nodes::types::visibilityType type = nodes::types::visibilityType::EXTERNAL,
				                 const std::vector<std::shared_ptr<compo::CPort> >& ports = std::vector<std::shared_ptr<compo::CPort>>(0));

			  public:

				/**
				* Accept method for visitor acceptation.
				* @param visitor: Pointer to abstract visitor.
				*/
				virtual void accept(std::shared_ptr<visitors::CAbstractVisitor> visitor) = 0;

				/**
				* visibility type getter
				* @return visibilityType
				*/
				nodes::types::visibilityType getVisibilityType() const;

				/**
				* Number of ports getter
				* @return number of ports of requirement
				*/
				size_t getNumberOfPorts() const;

				/**
				* Ports getter
				* @return port at given index
				*/
				std::shared_ptr<compo::CPort> getPortAt(unsigned int index) const;
			};

		}

	}

}