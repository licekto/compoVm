#pragma once

#include <map>

namespace nodes {

	namespace types {

		/**
		 * \enum NodeTypeEnum
		 * \brief Types of all nodes in AST
		 */
		enum operatorType {
			PLUS,
			MINUS,
			TIMES,
			DIVISION,
			EQUALITY,
			NON_EQUALITY,
			LOGICAL_OR,
			LOGICAL_AND,
			LESS,
			LESS_OR_EQUAL,
			GREATER,
			GREATER_OR_EQUAL
		};

		/**
		 * Function to print names of types
		 * @param type: type of node
		 */
		char operatorChar(operatorType type);

	}

}