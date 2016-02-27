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
			FOR,
			WHILE,
			IF,
			ELSE,
			CONSTANT,
			STRING_LITERAL,
			PARENS,
			ASSIGNMENT_EXPRESSION,
			ADDITIVE_EXPRESSION,
			MULTIPLICATIVE_EXPRESSION,
			LOGICAL_OR_EXPRESSION,
			LOGICAL_AND_EXPRESSION,
			EQUALITY_EXPRESSION
		};

		/**
		 * Function to print names of types
		 * @param type: type of node
		 */
		const char * typeName(nodeType type);

	}

}