#pragma once

#include <cstdint>
#include <string>
#include <map>

// types declaration
using i8 = int8_t;
using i32 = int32_t;
using i64 = int64_t;
using u8 = uint8_t;
using u32 = uint32_t;
using u64 = uint64_t;
using f32 = float;
using f64 = double;

#define IS_TYPE(node, type) (node->getNodeType() == type)

namespace types {

	/**
	* \enum nodeType
	* \brief Types of all nodes in AST
	*/
	enum nodeType {
		END = 0,
		PROGRAM,
		DESCRIPTOR,
		SYMBOL,
		SERVICE,
		SERVICE_SIGNATURE,
		PORT,
		CONSTRAINT,
		INTERFACE,
		ARCHITECTURE,
		CONNECTION,
		DISCONNECTION,
		DELEGATION,
		INJECTED_PORT,
		NAMED_PORT,
		SIGNATURES_PORT,
		UNIVERSAL_PORT,
		DEREFERENCE,
		COLLECTION_PORT,
		SERVICE_INVOCATION,
		PORT_ADDRESS,
		FOR,
		WHILE,
		IF,
		CONSTANT,
		BOOLEAN,
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
	std::string typeName(nodeType type);

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

	/**
	 * \enum roleType
	 * \brief Types of roles of ports
	 */
	enum roleType {
		REQUIRES,
		PROVIDES
	};

	/**
	* \enum portType
	* \brief Types of ports
	*/
	enum portType {
		EXPLICIT_LIST,
		UNIVERSAL,
		NAMED,
		INJECTED,
	};

	/**
	 * \enum visibilityType
	 * \brief Types of ports visibility
	 */
	enum visibilityType {
		INTERNAL,
		EXTERNAL,
	};

	/**
	* \enum valueComponentType
	 * \brief Types of value components
	 */
	enum valueComponentType {
		BOOL,
		INTEGER,
		STRING
	};
}