#pragma once

#include <map>

enum NodeTypeEnum {
    END = 0,
    DESCRIPTOR,
    SYMBOL,
    SERVICE,
    PORT,
    PROVISION,
    CONSTRAINT
};

const char * typeName(NodeTypeEnum type);