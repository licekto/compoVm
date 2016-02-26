#pragma once

#include "nodes/node.h"


namespace nodes {

    namespace procedural {

        /**
         * \class CCompoParens
         * \brief Class for expression in parentheses.
         */
        class CParens : public CNode {
        private:
                    CNode                       * m_expression;         /**< Expression in parentheses */

        public:
                                                    /**
                                                    * Parametric constructor with default values
                                                    * @param type: type of node
                                                    * @param val: integer value
                                                    */
                                                    CParens         (CNode *expr = nullptr);

                                                    /**
                                                    * Copy constructor
                                                    * Copy constructor is made protected to prevent from copying of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    */
                                                    CParens         (const CParens& other);

                                                    /**
                                                    * Move constructor
                                                    * Move constructor is made protected to prevent from moving of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    */
                                                    CParens         (CParens&& other) noexcept;

                                                    /**
                                                    * Copy assignment operator
                                                    * Copy assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CParens&                        operator =      (const CParens& other);

                                                    /**
                                                    * Move assignment operator
                                                    * Move assignment operator is made protected to prevent from assigning of object of this (abstract) type.
                                                    * @param other: rvalue-reference to another object of same type
                                                    * @return reference to assigned object
                                                    */
                    CParens&                        operator =      (CParens&& other) noexcept;

                                                    /**
                                                     * Clone method for copy-construction of polymorphic objects
                                                     * @return pointer to newly copied object.
                                                     */
            virtual CNode *                    clone           () const;

                                                    /**
                                                    * Virtual destructor
                                                    */
            virtual                                 ~CParens        ();

                                                    /**
                                                    * Virtual print function to call from operator <<
                                                    * @param os: output stream
                                                    * @see operator <<()
                                                    */
            virtual void                            print           (std::ostream& outStr) const;

                                                    /**
                                                     * Expression getter
                                                     * @return nodes::CNode pointer
                                                     */
                    nodes::CNode *                    getExpression   () const;
        };

    }
    
}