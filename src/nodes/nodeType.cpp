#include "nodeType.h"

std::map<NodeTypeEnum, const char *> typeNames = {
    {NodeTypeEnum::END, "End"},
    {NodeTypeEnum::DESCRIPTOR, "Descriptor"},
    {NodeTypeEnum::SYMBOL, "Symbol"},
    {NodeTypeEnum::SERVICE, "service"},
    {NodeTypeEnum::CONSTRAINT, "constraint"},
    {NodeTypeEnum::PORT, "port"},
    {NodeTypeEnum::PROVISION, "provides"}
};

const char * typeName(NodeTypeEnum type) {
    return typeNames[type];
}