#include "nodeType.h"

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
};

const char * typeName(NodeTypeEnum type) {
    return typeNames[type];
}