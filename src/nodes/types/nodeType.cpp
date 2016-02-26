#include "nodes/types/nodeType.h"

namespace nodes {

    namespace types {

        std::map<types::nodeTypeEnum, const char *> typeNames = {
            {types::nodeTypeEnum::END, "End"},
            {types::nodeTypeEnum::DESCRIPTOR, "Descriptor"},
            {types::nodeTypeEnum::SYMBOL, "Symbol"},
            {types::nodeTypeEnum::SERVICE, "service"},
            {types::nodeTypeEnum::PORT, "port"},
            {types::nodeTypeEnum::PROVISION, "provides"},
            {types::nodeTypeEnum::REQUIREMENT, "requires"},
            {types::nodeTypeEnum::CONSTRAINT, "constraint"},
            {types::nodeTypeEnum::INTERFACE, "interface"},
            {types::nodeTypeEnum::ARCHITECTURE, "architecture"},
            {types::nodeTypeEnum::CONNECTION, "connection"},
            {types::nodeTypeEnum::DISCONNECTION, "disconnection"},
            {types::nodeTypeEnum::INJECTED_PORT, "inject-with"},
        };

        const char * typeName(types::nodeTypeEnum type) {
            return typeNames[type];
        }

    }

}