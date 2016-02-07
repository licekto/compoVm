#pragma once

#include <map>

enum NodeTypeEnum {
    END = 0,
    DESCRIPTOR,
    SYMBOL,
    SERVICE,
    PORT,
    PROVISION
};

const char * typeName(NodeTypeEnum type);