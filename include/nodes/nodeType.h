#pragma once

#include <map>

enum NodeTypeEnum {
    END = 0,
    DESCRIPTOR,
    SYMBOL,
    SERVICE,
    PORT,
    PROVISION,
    REQUIREMENT,
    CONSTRAINT,
    INTERFACE,
    ARCHITECTURE,
    CONNECTION,
    DISCONNECTION,
    INJECTED_NODE
};

const char * typeName(NodeTypeEnum type);