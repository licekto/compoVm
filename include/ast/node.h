#pragma once

#include <iostream>
#include <vector>

#include "ast/types/nodeType.h"
#include "ast/visitor/abstractVisitor.h"

/**
 *  \addtogroup ast
 *  @{
 */

/**
 * ast Namespace to uniquely identify compo AST nodes.
 */
namespace ast {
	/**
	 * \class CNode
	 * \brief Abstract base class for other nodes.
	 *
	 * Abstract base class of AST. Every node in AST is derived from this one.
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
		friend std::ostream& operator <<(std::ostream& os, const CNode& node);

		/**
		 * Accept method for visitor acceptation.
		 * @param visitor: Pointer to abstract visitor.
		 */
		virtual void accept(ast::visitors::CAbstractVisitor *visitor) = 0;
	};

}

/*! @}*/