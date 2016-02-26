#pragma once

#include <map>

namespace compo {
    
    /**
     * \enum NodeTypeEnum
     * \brief Types of all nodes in AST
     */
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
        INJECTED_PORT,
        ASSIGNMENT,
        FOR,
        WHILE,
        IF,
        ELSE,
        CONSTANT,
        STRING_LITERAL
    };

    /**
     * Function to print names of types
     * @param type: type of node
     */
    const char * typeName(NodeTypeEnum type);

}