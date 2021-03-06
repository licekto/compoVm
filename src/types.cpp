#include "types.h"

namespace types {
	std::map<nodeType, const char *> typeNames = {
		{nodeType::END, "end"},
		{nodeType::PROGRAM, "program"},
		{nodeType::DESCRIPTOR, "descriptor"},
		{nodeType::SYMBOL, "symbol"},
		{nodeType::SERVICE, "service"},
		{nodeType::SERVICE_SIGNATURE, "service signature"},
		{nodeType::PORT, "port"},
		{nodeType::CONSTRAINT, "constraint"},
		{nodeType::INTERFACE, "interface"},
		{nodeType::ARCHITECTURE, "architecture"},
		{nodeType::CONNECTION, "connection"},
		{nodeType::DISCONNECTION, "disconnection"},
		{nodeType::DELEGATION, "delegation"},
		{nodeType::INJECTED_PORT, "injected port"},
		{nodeType::NAMED_PORT, "named port"},
		{nodeType::SIGNATURES_PORT, "signatures port"},
		{nodeType::UNIVERSAL_PORT, "universal port"},
		{nodeType::DEREFERENCE, "dereference"},
		{nodeType::COLLECTION_PORT, "collection port"},
		{nodeType::SERVICE_INVOCATION, "service invocation"},
		{nodeType::PORT_ADDRESS, "port address"},
		{nodeType::FOR, "for"},
		{nodeType::WHILE, "while"},
		{nodeType::IF, "if"},
		{nodeType::CONSTANT, "constant"},
		{nodeType::STRING_LITERAL, "string literal"},
		{nodeType::PARENS, "parens"},
		{nodeType::ASSIGNMENT_EXPRESSION, "assignment"},
		{nodeType::ADDITION_EXPRESSION, "addition"},
		{nodeType::SUBTRACTION_EXPRESSION, "subtraction"},
		{nodeType::DIVISION_EXPRESSION, "division"},
		{nodeType::MULTIPLICATION_EXPRESSION, "multiplication"},
		{nodeType::LOGICAL_OR_EXPRESSION, "or"},
		{nodeType::LOGICAL_AND_EXPRESSION, "and"},
		{nodeType::EQUALITY_EXPRESSION, "equality"},
		{nodeType::NON_EQUALITY_EXPRESSION, "nonequality"},
		{nodeType::LESS_EXPRESSION, "less"},
		{nodeType::LESS_OR_EQUAL_EXPRESSION, "less or equal"},
		{nodeType::GREATER_EXPRESSION, "greater"},
		{nodeType::GREATER_OR_EQUAL_EXPRESSION, "greater or equal"},
		{nodeType::COMPOUND_BODY, "compound body"},
		{nodeType::RETURN, "return"},
		{nodeType::BREAK, "break"},
		{nodeType::CONTINUE, "continue"},
		{nodeType::BOOLEAN, "boolean"},
	};

	std::string typeName(nodeType type) {
		return typeNames[type];
	}

	std::map<operatorType, char> operatorNames = {
		{operatorType::PLUS, '+'},
		{operatorType::MINUS, '-'},
		{operatorType::TIMES, '*'},
		{operatorType::DIVISION, '/'},
	};

	char operatorName(operatorType type) {
		return operatorNames[type];
	}
}