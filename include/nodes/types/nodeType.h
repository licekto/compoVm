#pragma once

#include <map>

namespace nodes {

	/**
	 *  \addtogroup types
	 *  @{
	 */

	/**
	 * types Namespace to uniquely identify compo AST nodes.
	 */
	namespace types {

		/**
		 * \enum nodeType
		 * \brief Types of all nodes in AST
		 */
		enum nodeType {
			END = 0,
			DESCRIPTOR,
			SYMBOL,
			SERVICE,
			PORT,
			PROVISION,
			REQUIREMENT,
			CONSTRAINT,
			INTERFACE,
			ARCHITECTURE,
			CONNECTION,
			DISCONNECTION,
			INJECTED_PORT,
			ASSIGNMENT,
			FOR,
			WHILE,
			IF,
			ELSE,
			CONSTANT,
			STRING_LITERAL,
			PARENS
		};

		/**
		 * Function to print names of types
		 * @param type: type of node
		 */
		const char * typeName(nodeType type);

	}

}