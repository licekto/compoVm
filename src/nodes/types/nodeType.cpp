#include "nodes/types/nodeType.h"

namespace nodes {

    namespace types {

        std::map<types::NodeTypeEnum, const char *> typeNames = {
            {types::NodeTypeEnum::END, "End"},
            {types::NodeTypeEnum::DESCRIPTOR, "Descriptor"},
            {types::NodeTypeEnum::SYMBOL, "Symbol"},
            {types::NodeTypeEnum::SERVICE, "service"},
            {types::NodeTypeEnum::PORT, "port"},
            {types::NodeTypeEnum::PROVISION, "provides"},
            {types::NodeTypeEnum::REQUIREMENT, "requires"},
            {types::NodeTypeEnum::CONSTRAINT, "constraint"},
            {types::NodeTypeEnum::INTERFACE, "interface"},
            {types::NodeTypeEnum::ARCHITECTURE, "architecture"},
            {types::NodeTypeEnum::CONNECTION, "connection"},
            {types::NodeTypeEnum::DISCONNECTION, "disconnection"},
            {types::NodeTypeEnum::INJECTED_PORT, "inject-with"},
        };

        const char * typeName(types::NodeTypeEnum type) {
            return typeNames[type];
        }

    }

}