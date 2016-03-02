#pragma once

#include <iostream>
#include <vector>

#include "nodes/types/nodeType.h"

/**
 *  \addtogroup nodes
 *  @{
 */

/**
 * nodes Namespace to uniquely identify compo AST nodes.
 */
namespace nodes {

	/**
	 * \class CNode
	 * \brief Abstract base class for other nodes.
	 *
	 * Abstract base class of AST. Every node in AST is inherited from this one.
	 *
	 * Rule of five is needed since CNode class has user-declared destructor.
	 */
	class CNode {
	  protected:
		/**< Type of node */
		types::nodeType m_nodeType;

		/**
		* Parametric constructor with default value
		* @param type: type of node
		*/
		CNode(types::nodeType type = types::nodeType::END);

	  public:

		/**
		* Virtual print function to call from operator <<
		* @param os: output stream
		* @see operator <<()
		*/
		virtual void print(std::ostream& os) const = 0;

		/**
		* NodeType getter
		* @return Type of node
		*/
		types::nodeType getNodeType() const;

		/**
		* Overloaded output operator
		* Operator calls virtual print method inside because of inheritance.
		* @param os: output stream
		* @param node: node to print
		* @see print()
		* @return Altered output stream
		*/
		friend  std::ostream& operator <<(std::ostream& os, const CNode& node);
	};

}

/*! @}*/