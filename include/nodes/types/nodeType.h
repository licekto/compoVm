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
			CONSTANT,
			STRING_LITERAL,
			PARENS,
			ASSIGNMENT_EXPRESSION,
			ADDITION_EXPRESSION,
			SUBTRACTION_EXPRESSION,
			DIVISION_EXPRESSION,
			MULTIPLICATION_EXPRESSION,
			LOGICAL_OR_EXPRESSION,
			LOGICAL_AND_EXPRESSION,
			EQUALITY_EXPRESSION,
			NON_EQUALITY_EXPRESSION,
			LESS_EXPRESSION,
			LESS_OR_EQUAL_EXPRESSION,
			GREATER_EXPRESSION,
			GREATER_OR_EQUAL_EXPRESSION,
			COMPOUND_BODY,
                        RETURN,
                        BREAK,
                        CONTINUE
		};

		/**
		 * Function to print names of types
		 * @param type: type of node
		 */
		const char * typeName(nodeType type);

	}

}