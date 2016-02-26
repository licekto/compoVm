#pragma once

#include <map>

namespace nodes {
    
    namespace types {
    
        /**
         * \enum NodeTypeEnum
         * \brief Types of all nodes in AST
         */
        enum operatorType {
            PLUS,
            MINUS,
            TIMES,
            DIVISION
        };

        /**
         * Function to print names of types
         * @param type: type of node
         */
        char operatorChar(operatorType type);

    }
    
}