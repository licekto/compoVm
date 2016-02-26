#pragma once

#include <map>

namespace nodes {
    
    namespace types {
    
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
            STRING_LITERAL,
            PARENS
        };

        /**
         * Function to print names of types
         * @param type: type of node
         */
        const char * typeName(NodeTypeEnum type);

    }
    
}