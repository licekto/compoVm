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
        INJECTED_NODE,
        ASSIGNMENT,
        FOR,
        WHILE,
        IF,
        ELSE
    };

    /**
     * Function to print names of types
     * @param type: type of node
     */
    const char * typeName(NodeTypeEnum type);

}