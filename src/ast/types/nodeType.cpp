#include "ast/types/nodeType.h"

namespace ast {

	namespace types {

		std::map<nodeType, const char *> typeNames = {
			{nodeType::END, "End"},
			{nodeType::DESCRIPTOR, "Descriptor"},
			{nodeType::SYMBOL, "Symbol"},
			{nodeType::SERVICE, "service"},
			{nodeType::PORT, "port"},
			{nodeType::PROVISION, "provides"},
			{nodeType::REQUIREMENT, "requires"},
			{nodeType::CONSTRAINT, "constraint"},
			{nodeType::INTERFACE, "interface"},
			{nodeType::ARCHITECTURE, "architecture"},
			{nodeType::CONNECTION, "connection"},
			{nodeType::DISCONNECTION, "disconnection"},
			{nodeType::INJECTED_PORT, "inject-with"},
		};

		const char * typeName(nodeType type) {
			return typeNames[type];
		}

	}

}