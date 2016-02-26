#include "nodes/compoTypes/nodeType.h"

namespace compo {
    
    std::map<NodeTypeEnum, const char *> typeNames = {
        {NodeTypeEnum::END, "End"},
        {NodeTypeEnum::DESCRIPTOR, "Descriptor"},
        {NodeTypeEnum::SYMBOL, "Symbol"},
        {NodeTypeEnum::SERVICE, "service"},
        {NodeTypeEnum::PORT, "port"},
        {NodeTypeEnum::PROVISION, "provides"},
        {NodeTypeEnum::REQUIREMENT, "requires"},
        {NodeTypeEnum::CONSTRAINT, "constraint"},
        {NodeTypeEnum::INTERFACE, "interface"},
        {NodeTypeEnum::ARCHITECTURE, "architecture"},
        {NodeTypeEnum::CONNECTION, "connection"},
        {NodeTypeEnum::DISCONNECTION, "disconnection"},
        {NodeTypeEnum::INJECTED_PORT, "inject-with"},
    };

    const char * typeName(NodeTypeEnum type) {
        return typeNames[type];
    }

}